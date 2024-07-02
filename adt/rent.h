#ifndef RENTADT_H
#define RENTADT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream> 
#include "computer.h"

using namespace std;

class RentADT {
public:
    void rentComputer() {
        computerADT.loadComputers(); 

        string name;
        cout << "Rent Computer\nComputer Name: ";
        cin.ignore();
        getline(cin, name);

        if (computerADT.checkComputerAvailability(name)) {
            computerADT.rentComputerByName(name);
            cout << "Computer Rented!" << endl;
        } else {
            cout << "Computer not available!" << endl;
        }
    }

    void returnComputer() {
        computerADT.returnComputer();
    }

    string getCurrentDate() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        stringstream ss; 
        ss << 1900 + ltm->tm_year << "-" 
           << 1 + ltm->tm_mon << "-" 
           << ltm->tm_mday;
        return ss.str();
    }

private:
    ComputerADT computerADT;
};

#endif
