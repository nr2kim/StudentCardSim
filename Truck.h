#ifndef __TRUCK_H
#define __TRUCK_H
#include "Printer.h"
#include "NameServer.h"
#include "MPRNG.h"
#include "VendingMachine.h"
extern MPRNG mprng;

_Task BottlingPlant;

_Task Truck {
    Printer *plantPrinter;
    NameServer *truckServer;
    BottlingPlant *bPlant;
    unsigned int numVending;
    unsigned int maxStock;
    unsigned int lastMachineId;
    VendingMachine **machineList;
    unsigned int *cargo;
    unsigned int *currStock;
    void main();
  public:
    Truck( Printer * prt, NameServer * nameServer, BottlingPlant * plant, unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
    ~Truck();
};
#endif
