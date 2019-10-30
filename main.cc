#include "config.h"
#include "MPRNG.h"
#include "NameServer.h"
#include "Printer.h"
#include "Bank.h"
#include "WATCardOffice.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include "VendingMachine.h"
#include "Groupoff.h"
#include "Student.h"
#include "BottlingPlant.h"
#include "Parent.h"

using namespace std;

MPRNG mprng;

int main(int argc, char * argv[]) {
	char * filename = NULL;
	unsigned int seed;
	seed = getpid();

	try {
		switch(argc) {
			case 3: seed = stoi( argv[2] ); if ( seed <= 0 ) { throw 1; }
			case 2: filename = argv[1];
			case 1: break;
		}
	} catch (...) {
		cout << "Usage: " << argv[0] << " [ config-file [ Seec ] ] " << endl;
	}

	mprng.set_seed(seed);
	if(filename == NULL) {
		char temp[12] = "soda.config";
		filename = temp;
	}

	ConfigParms config;
	processConfigFile( filename, config );

	Printer allPrinter( config.numStudents, config.numVendingMachines, config.numCouriers);
	Bank bank( config.numStudents );
	Parent myParent( allPrinter, bank, config.numStudents, config.parentalDelay);
	WATCardOffice watOffice( allPrinter, bank, config.numCouriers );
	Groupoff groupOff( allPrinter, config.numStudents, config.sodaCost, config.groupoffDelay);
	NameServer server( allPrinter, config.numVendingMachines, config.numStudents);
	VendingMachine * vending[config.numVendingMachines];
	for(int j = 0; j < config.numVendingMachines; j++) {
		vending[j] = new VendingMachine( allPrinter, server, j, config.sodaCost, config.maxStockPerFlavour);
	}
	{
		BottlingPlant plant( allPrinter, server, config.numVendingMachines, config.maxShippedPerFlavour, config.maxStockPerFlavour, config.timeBetweenShipments);

		Student * allStudent[config.numStudents];
		for(int i = 0; i < config.numStudents; i++) {
			allStudent[i] = new Student(allPrinter, server, watOffice, groupOff, i, config.maxPurchases);
		}

		for(int n = 0; n < config.numStudents; n++) {
			delete allStudent[n];
		}
	}
        for(int m = 0; m < config.numVendingMachines; m++) {
                delete vending[m];
        }
	return 0;
}
