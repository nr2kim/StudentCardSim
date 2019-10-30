#ifndef __NAMESERVER_H
#define __NAMESERVER_H
#include "Printer.h"

_Task VendingMachine;

_Task NameServer {
    Printer *serverPrinter;
    unsigned int numVendingMachine;
    VendingMachine ** serverManagement;
    int *student;
    void main();
  public:
    NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents );
    ~NameServer();

    void VMregister( VendingMachine * vendingmachine );
    VendingMachine * getMachine( unsigned int id );
    VendingMachine ** getMachineList();
};

#endif
