#pragma once
#include "uFuture.h"
#include <queue>
#include "Printer.h"
#include "Bank.h"
#include "MPRNG.h"

using std::queue;
extern MPRNG mprng;

class WATCard {
    unsigned int cardBalance;
    WATCard( const WATCard & ) = delete;      // prevent copying
    WATCard & operator=( const WATCard & ) = delete;
  public:
    typedef Future_ISM<WATCard *> FWATCard;   // future watcard pointer
    WATCard();
    ~WATCard();
    void deposit( unsigned int amount );
    void withdraw( unsigned int amount );
    unsigned int getBalance();
};

_Task WATCardOffice {
    struct Job {                              	// marshalled arguments and return future
        unsigned int studentId;			// call arguments (YOU DEFINE "Args")
	unsigned int transferAmount;
        WATCard::FWATCard result;             	// return future
	WATCard * jobCard;
        Job( unsigned int sid, unsigned int tAmount, WATCard * studentWat ) : studentId(sid), transferAmount(tAmount), jobCard(studentWat) {}
    };
    _Task Courier {
	Job *myJob;
	WATCardOffice *watOffice;
	Bank *myBank;
	unsigned int myId;
	void main();
	Printer * courPrinter;
	public:
	  Courier(unsigned int cid, Printer *prt, WATCardOffice *office, Bank * bank);
	  ~Courier();
    };                    // communicates with bank

    unsigned int numCourier;
    Printer * watPrinter;
    Bank * watBank;
    Courier **watCourier;
    queue<Job*> currentJob;
    void main();
  public:
    _Event Lost {};                           // lost WATCard
    WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers );
    ~WATCardOffice();
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard * card );
    Job * requestWork();
};
