#ifndef COMPUTERADT_H
#define COMPUTERADT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

using namespace std;

struct Computer {
    int id;
    string name;
    string specs;
    string brand;
    int units;
};

class ComputerADT {
public:
    void newComputer();
    void rentComputerByName(const string& name);
    void returnComputer();
    void showComputerDetails();
    void displayAllComputers();
    bool checkComputerAvailability(const string& name);
    const vector<Computer>& getComputers() const;

    void loadComputers();

private:
    const char* computerPath = "./data/computers.txt";
    vector<Computer> computers;

    int getNextID();
    void saveComputers();
    void displayComputer(const Computer& computer);
};

#endif
