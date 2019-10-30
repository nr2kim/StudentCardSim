#include "WATCardOffice.h"

WATCardOffice::Courier::Courier(unsigned int cid, Printer *prt, WATCardOffice *office, Bank * bank): watOffice(office), myId(cid), myBank(bank), courPrinter(prt) {}
WATCardOffice::Courier::~Courier() {}
void WATCardOffice::Courier::main() {
	courPrinter->print(Printer::Kind::Courier, myId, 'S');
	while(1) {
		_Accept( WATCardOffice::~Courier ) {
			break;
		} _Else {
			Job *myJob = watOffice->requestWork();
			if(mprng(1,6) == 1) {
				myJob->result.exception(new WATCardOffice::Lost);
				courPrinter->print(Printer::Kind::Courier, myId, 'L', myJob->studentId);
				delete myJob->jobCard;
			} else {
				courPrinter->print(Printer::Kind::Courier, myId, 't', myJob->studentId, myJob->transferAmount);
	        		myBank->withdraw(myJob->studentId, myJob->transferAmount);
				myJob->jobCard->deposit(myJob->transferAmount);
        			myJob->result.delivery(myJob->jobCard);
				courPrinter->print(Printer::Kind::Courier, myId, 'T', myJob->studentId, myJob->transferAmount);
			}
		}
	}
	courPrinter->print(Printer::Kind::Courier, myId, 'F');
}
