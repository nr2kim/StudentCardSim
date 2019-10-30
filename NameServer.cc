#include "NameServer.h"
#include "VendingMachine.h"
NameServer::NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents ) : serverPrinter(&prt), numVendingMachine(numVendingMachines) {
        serverManagement = new VendingMachine*[numVendingMachines];
        // initialize the vendingmachine pointers
        for(int j = 0; j < numVendingMachines; j++) {
                serverManagement[j] = NULL;
        }

        student = new int[numStudents];
        // initialize mapping of student and vendingmachines
        for(int i = 0; i < numStudents; i++) {
                student[i] = i % numVendingMachines;
        }
}
NameServer::~NameServer() {
	delete []serverManagement;
}

void NameServer::VMregister( VendingMachine * vendingmachine ) {
        // register VM in servermanagement
        serverManagement[vendingmachine->getId()] = vendingmachine;
	serverPrinter->print(Printer::Kind::NameServer, 'R', vendingmachine->getId());
}

VendingMachine * NameServer::getMachine( unsigned int id ) {
        unsigned int currMachine = student[id];
        // increment it for the next time
	student[id] = (student[id] + 1 ) % numVendingMachine;

	if(id % numVendingMachine != currMachine) {
		serverPrinter->print(Printer::Kind::NameServer, 'N', id, student[id]);
        }
	return serverManagement[currMachine];
}

VendingMachine ** NameServer::getMachineList() {
	return serverManagement;
}

void NameServer::main() {
	serverPrinter->print(Printer::Kind::NameServer, 'S');
        for(int i = 0; i < numVendingMachine; i++) {
                _Accept( VMregister );
        }
        while(1) {
                _Accept( ~NameServer ) {
                        break;
                } or _Accept( getMachine );
                or _Accept( getMachineList );
        }
	serverPrinter->print(Printer::Kind::NameServer, 'F');
}
