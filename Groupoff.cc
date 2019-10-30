#include "Groupoff.h"

Groupoff::Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay ) : groupoffPrinter(&prt), numStudent(numStudents), costSoda(sodaCost), delay(groupoffDelay), count(0) {
        gift = new WATCard::FWATCard[numStudent];

        for(int i = 0; i < numStudent; i++) {
                depositCard.push_back(i);
        }
}
Groupoff::~Groupoff() {
        delete [] gift;
}

WATCard::FWATCard Groupoff::giftCard() {
        return gift[count];
}

void Groupoff::main() {
	groupoffPrinter->print(Printer::Kind::Groupoff, 'S');
        for(; count < numStudent; count++) {
                _Accept(giftCard);
        }
        while(1) {
                _Accept( ~Groupoff ) {
                        break;
                } _Else {
			WATCard realGift;
                        if(depositCard.empty()) break;

                        // TODO::or all the real WATCards are assigned ot a future gift-card
                        yield(delay);
                        unsigned int toGive = mprng(0, depositCard.size() -1);
                        unsigned int giftAtToGive = depositCard.at(toGive);
			groupoffPrinter->print(Printer::Kind::Groupoff, 'D', giftAtToGive);
			realGift.deposit(costSoda);
                        gift[giftAtToGive].delivery(&realGift);
                        depositCard.erase(depositCard.begin() + toGive);
                }
        }
	groupoffPrinter->print(Printer::Kind::Groupoff, 'F');
}
