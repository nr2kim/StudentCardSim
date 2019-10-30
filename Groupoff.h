#ifndef __GROUPOFF_H
#define __GROUPOFF_H

#include "MPRNG.h"
#include "Printer.h"
#include "WATCardOffice.h"

extern MPRNG mprng;

_Task Groupoff {
    Printer *groupoffPrinter;
    unsigned int numStudent;
    unsigned int costSoda;
    unsigned int delay;
    unsigned int count;
    WATCard::FWATCard *gift;
    std::vector<unsigned int> depositCard;
    void main();
  public:
    Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
    ~Groupoff();

    WATCard::FWATCard giftCard();
};

#endif
