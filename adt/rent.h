#ifndef RENTADT_H
#define RENTADT_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include "computer.h"
#include "customer.h"

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

using namespace std;

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

class RentADT {
public:
    void rentComputer(ComputerADT& computerADT, int customerId, const string& computerName) {
        computerADT.loadComputers();
        const vector<Computer>& computers = computerADT.getComputers();

        bool computerAvailable = false;
        for (const auto& computer : computers) {
            if (computer.name == computerName && computer.units > 0) {
                computerAvailable = true;
                break;
            }
        }

        if (!computerAvailable) {
            cout << RED << "Computer Not Available!" << RESET << endl;
            waitForUserInput();
            return;
        }

        loadRents();
        Rent rent;
        rent.id = getNextID();
        rent.customerId = customerId;
        rent.computerName = computerName;
        rent.rentDate = getCurrentDate();
        rent.returnDate = "Not Returned";

        rents.push_back(rent);
        saveRents();
        computerADT.rentComputerByName(computerName);
        cout << GREEN << "Computer Rented!" << RESET << endl;
        waitForUserInput();
    }

private:
    struct Rent {
        int id;
        int customerId;
        string computerName;
        string rentDate;
        string returnDate;
    };

    const char* rentPath = "./data/rents.txt";
    vector<Rent> rents;

    int getNextID() {
        return rents.empty() ? 1 : rents.back().id + 1;
    }

    void loadRents() {
        ifstream file(rentPath);
        if (!file) {
            cout << RED << "Unable to open file." << RESET << endl;
            return;
        }

        rents.clear();
        Rent rent;
        string line;
        while (getline(file, line)) {
            if (line.find("ID: ") == 0) {
                rent.id = stoi(line.substr(4));
            } else if (line.find("CustomerID: ") == 0) {
                rent.customerId = stoi(line.substr(12));
            } else if (line.find("ComputerName: ") == 0) {
                rent.computerName = line.substr(14);
            } else if (line.find("RentDate: ") == 0) {
                rent.rentDate = line.substr(10);
            } else if (line.find("ReturnDate: ") == 0) {
                rent.returnDate = line.substr(12);
            } else if (line == "---") {
                rents.push_back(rent);
            }
        }
        file.close();
    }

    void saveRents() {
        #ifdef _WIN32
        _mkdir("./data");
        #else
        mkdir("./data", 0777);
        #endif

        ofstream file(rentPath);
        if (!file) {
            cout << RED << "Unable to open file." << RESET << endl;
            return;
        }

        for (const auto& rent : rents) {
            file << "ID: " << rent.id << '\n'
                 << "CustomerID: " << rent.customerId << '\n'
                 << "ComputerName: " << rent.computerName << '\n'
                 << "RentDate: " << rent.rentDate << '\n'
                 << "ReturnDate: " << rent.returnDate << '\n'
                 << "---\n";
        }

        file.close();
    }

    string getCurrentDate() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        stringstream ss;
        ss << 1900 + ltm->tm_year << "-"
           << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-"
           << setfill('0') << setw(2) << ltm->tm_mday;
        return ss.str();
    }

    void waitForUserInput() {
        cout << YELLOW << "Press enter to continue..." << RESET;
        cin.ignore();
        cin.get();
    }
};

#endif