#include "BottlingPlant.h"

BottlingPlant::BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines, unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments ) : plantPrinter(&prt), plantServer(&nameServer), numVending(numVendingMachines), maxShipPerFlavour(maxShippedPerFlavour), maxStockFlavour(maxStockPerFlavour), timeBetweenShips(timeBetweenShipments), shutDownFlag(false) {}
BottlingPlant::~BottlingPlant() {}
void BottlingPlant::getShipment( unsigned int cargo[] ) {
	if(shutDownFlag) {
		uRendezvousAcceptor();
		_Throw Shutdown();
	}

        for(int i = 0; i < 4; i++) {
                cargo[i] = produce[i];
        }
}

void BottlingPlant::main() {
	Truck myTruck( plantPrinter, plantServer, this, numVending, maxStockFlavour);
	plantPrinter->print(Printer::Kind::BottlingPlant, 'S');
	while(1) {
		unsigned int produced = 0;
                for(int i = 0; i < 4; i++) {
                        produce[i] = mprng(0, maxShipPerFlavour);
			produced++;
                }

		plantPrinter->print(Printer::Kind::BottlingPlant, 'G', produced);
                yield(timeBetweenShips);

                _Accept( ~BottlingPlant ) {
			shutDownFlag = true;
			_Accept( getShipment );
                        break;
                }
                or _Accept( getShipment ) {
			plantPrinter->print(Printer::Kind::BottlingPlant, 'P');
		}
        }
	plantPrinter->print(Printer::Kind::BottlingPlant, 'F');
}
