#ifndef __PARENT_H
#define __PARENT_H

#include "MPRNG.h"

extern MPRNG mprng;

_Task Parent {
    Printer *parentPrinter;
    Bank *parentBank;
    unsigned int numStudent;
    unsigned int delay;
    void main() {
	parentPrinter->print(Printer::Kind::Parent, 'S');
	while(1) {
		_Accept( ~Parent ) {
			break;
		} _Else {
			yield(delay);
			unsigned int depositTo = mprng(0, numStudent-1);
			unsigned int depositAmount = mprng(1,3);
			parentPrinter->print(Printer::Kind::Parent, 'D', depositTo, depositAmount);
			parentBank->deposit(depositTo, depositAmount);
		}
	}
	// Parent must check for a call to its destructor to know when to terminate
	// since it must not block on this call, it is necessary to use a terminating _Else on the accept statement
	// Hence the parent is busy waiting for the call to its destructor
	parentPrinter->print(Printer::Kind::Parent, 'F');
    }

  public:
    Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay ) : parentPrinter(&prt), parentBank(&bank), numStudent(numStudents), delay(parentalDelay) {}
    ~Parent() {}
};
#endif
