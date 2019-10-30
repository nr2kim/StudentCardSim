#include "Truck.h"
#include "BottlingPlant.h"
Truck::Truck( Printer * prt, NameServer * nameServer, BottlingPlant * plant, unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) : plantPrinter(prt), truckServer(nameServer), bPlant(plant), numVending(numVendingMachines), maxStock(maxStockPerFlavour) {
        machineList = nameServer->getMachineList();
	cargo = new unsigned int[4];
}
Truck::~Truck() {}

void Truck::main() {
	unsigned int total = 0;
	plantPrinter->print(Printer::Kind::Truck, 'S');
	while(1) {
                yield(mprng(1,10));                                     // get a coffee from Tom Hortons
                try {
	                bPlant->getShipment(cargo);
			total = cargo[0] + cargo[1] + cargo[2] + cargo[3];
			plantPrinter->print(Printer::Kind::Truck, 'P', total);
                } catch ( BottlingPlant::Shutdown ) {
			
			plantPrinter->print(Printer::Kind::Truck, 'F');
                        break;
                }

                unsigned int startingMachineId = lastMachineId;
                while((cargo[0] > 0 || cargo[1] > 0 || cargo[2] > 0 || cargo[3] > 0)) {
			plantPrinter->print(Printer::Kind::Truck, 'd', lastMachineId, total);
                        currStock = machineList[lastMachineId]->inventory();
			unsigned int unfilled = 4 * maxStock;
                        for(int i = 0; i < 4; i++) {
				unfilled -= currStock[i];
                                while(cargo[i] > 0 && currStock[i] < maxStock) {
					unfilled--;
                                        currStock[i] = currStock[i] + 1;
                                        cargo[i]--;
					total--;
                                }
                        }
			if(unfilled > 0)
				plantPrinter->print(Printer::Kind::Truck, 'U', lastMachineId, unfilled);
			plantPrinter->print(Printer::Kind::Truck, 'D', lastMachineId, total);
			machineList[lastMachineId]->restocked();
			lastMachineId = (lastMachineId + 1) % numVending;
			if(startingMachineId == lastMachineId)
				break;
                }
        }
	plantPrinter->print(Printer::Kind::Truck, 'F');
}
