#ifndef __STUDENT_H
#define __STUDENT_H

#include "Printer.h"
#include "NameServer.h"
#include "WATCardOffice.h"
#include "Groupoff.h"
#include "VendingMachine.h"
extern MPRNG mprng;

_Task Student {
    unsigned int myId;
    unsigned int maxPurchase;
    unsigned int currentNumBottlePurchase;
    Printer * studentPrinter;
    NameServer * studentServer;
    WATCardOffice * watOffice;
    Groupoff * studentGroupOff;
    VendingMachine * myVendingMachine;
    WATCard::FWATCard myWATCard;
    WATCard::FWATCard myGiftCard;
    void main() {
	// a student starts by selecting a random number of bottles to purchase [1, MaxPurchases]
	currentNumBottlePurchase = mprng(1, maxPurchase);
	// a random favourite flavour [0, 3]
	VendingMachine::Flavours myFlavour = (VendingMachine::Flavours)mprng(0, 3);

	studentPrinter->print(Printer::Kind::Student, myId, 'S', myFlavour, currentNumBottlePurchase);	
	// create WATCard via the WATCardOffice with a $5 balance
	myWATCard = watOffice->create(myId, 5);
	//create a giftcard via the Groupoff with a value of SodaCost
	myGiftCard = studentGroupOff->giftCard();
	// obtain the location of a vending machine from the name server
	myVendingMachine = studentServer->getMachine(myId);
	studentPrinter->print(Printer::Kind::Student, myId, 'V', myVendingMachine->getId());
	// terminates after purchasing all the soda initially selected
	for( int i = 0; i < currentNumBottlePurchase; i++) {
		// Before each attempt to buy a soda, a student yields a random number of times in the range [1, 10]
		yield(mprng(1,10));
		while(1) {
			// may need to wait for money to be transferred either to their WATCard or to their gift card
			try {
				_Select( myWATCard ) {
					// once money is available on either card, the student can attempt to buy a bottle of soda from their current vending machine
					try {
						myVendingMachine->buy(myFlavour, *myWATCard);
					} catch ( VendingMachine::Funds ) {
	        	        	        myWATCard = watOffice->transfer(myId, myVendingMachine->cost() + 5, myWATCard());
        	  	        	      // attempts another purchase
                			        i--; // because did not purchase it, but will be incremented at the end of this catch clause, decrementing it for now
					} catch ( VendingMachine::Stock ) {
						// student must obtain a new vending machine from the name server and attempt another purchase
			                        myVendingMachine = studentServer->getMachine(myId);
			                        i--; // because did not purchase it, decrementing it because it will be incremented at the end of this catch clause
                                        } catch ( VendingMachine::Free) {
                                                yield(4);
                                                studentPrinter->print(Printer::Kind::Student, myId, 'a', myFlavour, (*myWATCard()).getBalance());
                                                break;
					}
					studentPrinter->print(Printer::Kind::Student, myId, 'B', myFlavour, (*myWATCard()).getBalance());
					break;
			 
				} or _Select( myGiftCard ) {
					// once money is available on either card, the student can attempt to buy a bottle of soda from their current vending machine
					try {
						myVendingMachine->buy(myFlavour, *myGiftCard);
					} catch ( VendingMachine::Funds ) {
						myWATCard = watOffice->transfer(myId, myVendingMachine->cost() + 5, myWATCard());
			                        // attempts another purchase
			                        i--; // because did not purchase it, but will be incremented at the end of this catch clause, decrementing it for now
					} catch ( VendingMachine::Stock ) {
						// student must obtain a new vending machine from the name server and attempt another purchase
			                        myVendingMachine = studentServer->getMachine(myId);
			                        i--; // because did not purchase it, decrementing it because it will be incremented at the end of this catch clause
					} catch (VendingMachine::Free ) {
						yield(4);
						studentPrinter->print(Printer::Kind::Student, myId, 'A', myFlavour, (*myGiftCard()).getBalance());
						break;
					}
					studentPrinter->print(Printer::Kind::Student, myId, 'G', myFlavour, (*myGiftCard()).getBalance());
					// giftcard future can only be used once; need to be reset.
					myGiftCard.reset();
					break;
				}
			} catch ( WATCardOffice::Lost ) {
				// Catch WATCardOffice::Lost from Courier when future value is accessed
				// then new watcard
				myWATCard = watOffice->create(myId, 5);
				studentPrinter->print(Printer::Kind::Student, myId, 'L');
			}
		}
	}

	studentPrinter->print(Printer::Kind::Student, myId, 'F');
	
    }
  public:
    Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff, unsigned int id, unsigned int maxPurchases ): studentPrinter(&prt), studentServer(&nameServer), watOffice(&cardOffice), studentGroupOff(&groupoff), myId(id), maxPurchase(maxPurchases) {}
    ~Student() {}
};
#endif
