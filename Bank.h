#ifndef __BANK_H
#define __BANK_H

_Monitor Bank {
    unsigned int * balance;
  public:
    Bank( unsigned int numStudents );
    ~Bank();
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
};

#endif
