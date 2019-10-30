#include "VendingMachine.h"

extern MPRNG mprng;

VendingMachine::VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour ) : vendingPrinter(&prt), vendingServer(vendingServer), vendingId(id), sodaPrice(sodaCost), maxStockFlavour(maxStockPerFlavour) {
        stockPerFlavour = new unsigned int[4];
        for( int i = 0; i < 4; i++) {
                stockPerFlavour[i] = 0;
        }
        nameServer.VMregister(this);
}

VendingMachine::~VendingMachine() {
	delete [] stockPerFlavour;
}
void VendingMachine::main() {
	vendingPrinter->print(Printer::Kind::Vending, vendingId,'S');
	while(1) {
		_Accept(~VendingMachine) {
			break;
		}
                or _Accept ( buy ); 
                or _Accept ( inventory ) {
                        _Accept( restocked );
                }
        }
	vendingPrinter->print(Printer::Kind::Vending, vendingId, 'F');
}
void VendingMachine::buy( Flavours flavour, WATCard & card ) {
        if(card.getBalance() < sodaPrice) {
		uRendezvousAcceptor();
                _Throw Funds();
        } else if(stockPerFlavour[flavour] == 0) {
		uRendezvousAcceptor();
                _Throw Stock();
        } else if(mprng(1,5) == 1) {                    // FREEEEE
                stockPerFlavour[flavour] = stockPerFlavour[flavour] - 1;
		vendingPrinter->print(Printer::Kind::Vending, vendingId, 'B', flavour, stockPerFlavour[flavour]);
		uRendezvousAcceptor();
                _Throw Free();
        } else {
                stockPerFlavour[flavour] = stockPerFlavour[flavour] -1;
		vendingPrinter->print(Printer::Kind::Vending, vendingId, 'B', flavour, stockPerFlavour[flavour]);
                card.withdraw(sodaPrice);
        }
}

unsigned int * VendingMachine::inventory() {
	vendingPrinter->print(Printer::Kind::Vending, vendingId, 'r');
	return stockPerFlavour;
}

void VendingMachine::restocked() {
	vendingPrinter->print(Printer::Kind::Vending, vendingId, 'R');
	// operation of restocking complete, do nothing
}

unsigned int VendingMachine::cost() {
        return sodaPrice;
}
unsigned int VendingMachine::getId() {
        return vendingId;
}

