#ifndef __BOTTLINGPLANT_H
#define __BOTTLINGPLANT_H

#include "MPRNG.h"
#include "Truck.h"

extern MPRNG mprng;

_Task BottlingPlant {
    Printer *plantPrinter;
    NameServer *plantServer;
    unsigned int numVending;
    unsigned int maxShipPerFlavour;
    unsigned int maxStockFlavour;
    unsigned int timeBetweenShips;
    bool shutDownFlag;
    unsigned int produce[4];
    void main();
  public:
    _Event Shutdown {};                       // shutdown plant
    BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines, unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments );
    ~BottlingPlant();
    void getShipment( unsigned int cargo[] );
};
#endif
