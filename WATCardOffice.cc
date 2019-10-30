#include "WATCardOffice.h"

WATCard::WATCard() : cardBalance(0) {}
WATCard::~WATCard() {}
void WATCard::deposit( unsigned int amount ) {
        cardBalance += amount;
}
void WATCard::withdraw( unsigned int amount ) {
        cardBalance -= amount;
}
unsigned int WATCard::getBalance() {
        return cardBalance;
}

WATCardOffice::WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers ): watPrinter(&prt), watBank(&bank), numCourier(numCouriers) {
        watCourier = new Courier*[numCouriers];
	for(unsigned int i = 0; i < numCouriers; i++) {
		watCourier[i] = new Courier(i , watPrinter, this, watBank);
	}
}

WATCardOffice::~WATCardOffice() {
	for(unsigned int m = 0; m < numCourier; m++) {
	        delete watCourier[m];
	}
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
	WATCard * newCard = new WATCard();
	Job *thisJob = new Job(sid, amount, newCard);
	currentJob.push(thisJob);
	watPrinter->print(Printer::Kind::WATCardOffice, 'C', sid, amount);
        // let Courier to withdraw money from bank
        return thisJob->result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard * card ) {
        Job *thisJob = new Job(sid, amount, card);
	currentJob.push(thisJob);
	watPrinter->print(Printer::Kind::WATCardOffice, 'T', sid, amount);
        return thisJob->result;
}

WATCardOffice::Job * WATCardOffice::requestWork() {
	if(currentJob.size() == 0)
		_Accept(create, transfer);
	Job * nextJob = currentJob.front();
	currentJob.pop();
	watPrinter->print(Printer::Kind::WATCardOffice, 'W');
	return nextJob;
}

void WATCardOffice::main() {
	watPrinter->print(Printer::Kind::WATCardOffice, 'S');
	while(1) {
		_Accept( ~WATCardOffice ) break;
		or _Accept ( create, transfer, requestWork );
	}
	watPrinter->print(Printer::Kind::WATCardOffice, 'F');

}
