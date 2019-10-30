#ifndef __PRINTER_H
#define __PRINTER_H

#include <iostream>
#include <string>

using namespace std;
_Monitor Printer {
    unsigned int total;
    unsigned int numStudent;
    unsigned int numVendingMachine;
    unsigned int numCourier;
    char **buffer;
    void initBuffer() {
	for(unsigned int a = 0; a < total; a++) {
		for(int i = 0; i < 8; i++) {
			buffer[a][i] = ' ';
		}
	}
    }

    void printBuffer() {
	for(unsigned int n = 0; n < total; n++) {
		for(int l = 0; l < 8; l++) {
			cout << buffer[n][l];
		}
	}
	cout << endl;
	initBuffer();
    }

    bool isBufferEmpty() {
	for(unsigned int n = 0; n < total; n++) {
		if(!isspace(buffer[n][0]))
			return false;
	}
	return true;
    }

  public:
    enum Kind { Parent, Groupoff, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    bool checkBufferOverwrite(Kind checkKind) {
	if(isspace(buffer[checkKind][0]))
                return false;
        return true;
    }

    bool checkBufferOverwrite(Kind checkKind, unsigned int id) {
	if(checkKind == Student && isspace(buffer[6+id][0])) {
                return false;
        } else if(checkKind == Vending && isspace(buffer[6+numStudent+id][0])) {
                return false;
        } else if(checkKind == Courier && isspace(buffer[6+numStudent+numVendingMachine+id][0])) {
                return false;
        }
        return true;
    }

    unsigned int getPos(Kind kind, unsigned int id) {
	if(kind == Student)
		return 6+id;
	else if(kind == Vending)
		return 6+numStudent+id;
	else if(kind == Courier)
		return 6+numStudent+numVendingMachine;
	return -1;
    }

    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) : numStudent(numStudents), numVendingMachine(numVendingMachines), numCourier(numCouriers) {
	total = 6 + numStudents + numVendingMachines + numCouriers;
	buffer = new char*[total];
	// initialization of buffer
	for(unsigned int i = 0; i < total; i++) {
		buffer[i] = new char[8];
	}

	initBuffer();
	cout << "Parent\tGropoff\tWATOff\tNames\tTruck\tPlant\t";

	for(unsigned int j = 0; j < numStudents; j++) {
		cout << "Stud" << j << "\t";
	}

	for(unsigned int m = 0; m < numVendingMachines; m++) {
		cout << "Mach" << m << "\t";
	}

	for(unsigned int c = 0; c < numCouriers; c++) {
		cout << "Cour" << c << "\t";
	}
	
	cout << endl;

	for(unsigned int a = 0; a < total; a++ ) {
		cout << "*******\t";
	}

	cout << endl;

    }
    ~Printer() {
	if(!isBufferEmpty()) {
		printBuffer();
	}
	
	for(unsigned int j = 0; j < total; j++) {
		delete []buffer[j];
	}
	delete [] buffer;
	cout << "****************" << endl;
	cout << "All tours started" << endl;
    }

    void print( Kind kind, char state ) {
	if(checkBufferOverwrite(kind)) printBuffer();
	buffer[kind][0] = state;
    }
	
    void print( Kind kind, char state, int value1 ) {
	if(checkBufferOverwrite(kind)) printBuffer();
	buffer[kind][0] = state;
	string nb = to_string(value1);
	char tempCharArray[nb.length()];
	strcpy(tempCharArray, nb.c_str());
	for(unsigned int i = 0; i < nb.length(); i++) {
		buffer[kind][1+i] = tempCharArray[i];
	}
    }

    void print( Kind kind, char state, int value1, int value2 ) {
	if(checkBufferOverwrite(kind)) printBuffer();
	buffer[kind][0] = state;
	string nb = to_string(value1);
	char tempCharArray[nb.length()];
	strcpy(tempCharArray, nb.c_str());
	for(unsigned int i = 0; i < nb.length(); i++) {
		buffer[kind][1+i] = tempCharArray[i];
	}

	buffer[kind][1+nb.length()] = ',';
	string nc = to_string(value2);
	char tempCharArray2[nc.length()];
	strcpy(tempCharArray2, nc.c_str());
	assert(nb.length() + nc.length() + 2 < 8);
	for(unsigned int j = 0; j < nc.length() ; j++) {
		buffer[kind][2+nb.length()+j] = tempCharArray2[j];
	}
    }
    void print( Kind kind, unsigned int lid, char state ) {
	unsigned int pos = getPos(kind, lid);
	if(checkBufferOverwrite(kind, lid)) printBuffer();
	buffer[pos][0] = state;
    }

    void print( Kind kind, unsigned int lid, char state, int value1 ) {
	unsigned int pos = getPos(kind, lid);
	if(checkBufferOverwrite(kind, lid)) printBuffer();
	buffer[pos][0] = state;
	string nb = to_string(value1);
	char tempCharArray[nb.length()];
	strcpy(tempCharArray, nb.c_str());
	for(unsigned int i=0; i< nb.length(); i++) {
		buffer[pos][i+1] = tempCharArray[i];
	}
    }
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {
	unsigned int pos = getPos(kind, lid);
	if(checkBufferOverwrite(kind, lid)) printBuffer();
	buffer[pos][0] = state;
	string nb = to_string(value1);
	char tempCharArray[nb.length()];
	strcpy(tempCharArray, nb.c_str());
	for(unsigned int i = 0; i < nb.length(); i++) {
		buffer[pos][i+1] = tempCharArray[i];
	}
	
	buffer[pos][1+nb.length()] = ',';
	string nc = to_string(value2);
	char tempCharArray2[nc.length()];
	strcpy(tempCharArray2, nc.c_str());
	assert(nb.length() + nc.length() + 2 < 8);
	for(unsigned int j = 0; j < nc.length(); j++) {
		buffer[pos][2+nb.length()+j] = tempCharArray2[j];
	}
    }
};

#endif
