#ifndef __VENDINGMACHINE_H
#define __VENDINGMACHINE_H

#include "MPRNG.h"
#include "Printer.h"
#include "NameServer.h"
#include "WATCardOffice.h"

_Task VendingMachine {
    Printer *vendingPrinter;
    NameServer *vendingServer;
    unsigned int vendingId;
    unsigned int *stockPerFlavour;
    unsigned int maxStockFlavour;
    unsigned int sodaPrice;
    void main();
  public:
    enum Flavours { BlueBlackCherry, ClassicCreamSoda, RockRootBeer, JazzLime};                    // flavours of soda (YOU DEFINE)
    _Event Free {};                           // free, advertisement
    _Event Funds {};                          // insufficient funds
    _Event Stock {};                          // out of stock for particular flavour
    VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour );
    ~VendingMachine();
    void buy( Flavours flavour, WATCard & card );
    unsigned int * inventory();
    void restocked();

    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};

#endif
