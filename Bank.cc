#include "Bank.h"

Bank::Bank( unsigned int numStudents ) {
	balance = new unsigned int[numStudents];
        for(int i = 0 ; i < numStudents; i++) {
                balance[i] = 0;
        }
}
Bank::~Bank() {
	delete [] balance;
}
void Bank::deposit( unsigned int id, unsigned int amount ) {
        balance[id] += amount;
}
void Bank::withdraw( unsigned int id, unsigned int amount ) {
        while(balance[id] < amount) {
                _Accept(deposit);
        }

        balance[id] -= amount;
}
