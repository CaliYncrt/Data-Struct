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

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

struct Computer {
    int id;
    string name;
    string specs;
    string brand;
    int units;
};

class ComputerADT {
public:
    void waitForInput() {
        cout << YELLOW << "Press enter to continue..." << RESET;
        cin.ignore();
    }

    void addNewComputer() {
        loadComputers();

        Computer computer;
        computer.id = generateID();

        cout << GREEN << "Add New Computer\nComputer Name: " << RESET;
        cin.ignore();
        getline(cin, computer.name);
        cout << GREEN << "Specifications: " << RESET;
        getline(cin, computer.specs);
        cout << GREEN << "Brand: " << RESET;
        getline(cin, computer.brand);
        cout << GREEN << "Number of Units: " << RESET;
        cin >> computer.units;

        computers.push_back(computer);
        saveComputers();
        cout << GREEN << "New Computer Added!" << RESET << endl;
        cin.ignore();
    }

    void rentComputerByName(const string& name) {
        loadComputers();

        for (auto& computer : computers) {
            if (computer.name == name) {
                if (computer.units > 0) {
                    computer.units--;
                    saveComputers();
                    return;
                }
            }
        }
    }

    void returnComputer() {
        loadComputers();

        string name;
        bool computerFound = false;
        cout << GREEN << "Return Computer\nComputer Name: " << RESET;
        cin.ignore();
        getline(cin, name);

        for (auto& computer : computers) {
            if (computer.name == name) {
                computerFound = true;
                computer.units++;
                saveComputers();
                cout << GREEN << "Computer Returned!" << RESET << endl;
                waitForInput();
                return;
            }
        }
        if (!computerFound) {
            cout << RED << "Computer Name Not Found!" << RESET << endl;
            waitForInput();
        }
    }

    void showComputerDetails() {
        loadComputers();

        string name;
        cout << GREEN << "Show Computer Details\nComputer Name: " << RESET;
        cin.ignore();
        getline(cin, name);
        bool computerFound = false;

        for (const auto& computer : computers) {
            if (computer.name == name) {
                computerFound = true;
                cout << GREEN << "ID: " << RESET << computer.id << "\n" << GREEN << "Name: " << RESET << computer.name << "\n" << GREEN << "Specifications: " << RESET << computer.specs << "\n" << GREEN << "Brand: " << RESET << computer.brand << "\n" << GREEN << "Units: " << RESET << computer.units << endl;
                waitForInput();
                return;
            }
        }
        if (!computerFound) {
            cout << RED << "Computer Name Not Found!" << RESET << endl;
            waitForInput();
        }
    }

    void displayAllComputers() {
        loadComputers();

        for (const auto& computer : computers) {
            cout << GREEN << "ID: " << RESET << computer.id << "\n" << GREEN << "Name: " << RESET << computer.name << "\n" << GREEN << "Specifications: " << RESET << computer.specs << "\n" << GREEN << "Brand: " << RESET << computer.brand << "\n" << GREEN << "Units: " << RESET << computer.units << endl;
        }
        waitForInput();
        cin.ignore();
    }

    bool checkComputerAvailability(const string& name) {
        loadComputers();

        for (const auto& computer : computers) {
            if (computer.name == name && computer.units > 0) {
                return true;
            }
        }
        return false;
    }

    const vector<Computer>& getComputers() const {
        return computers;
    }

    void loadComputers() {
        ifstream file(computerPath);
        if (!file) {
            cout << RED << "Unable to open file." << RESET << endl;
            return;
        }

        computers.clear();
        Computer computer;
        string line;
        while (getline(file, line)) {
            if (line.find("ID: ") == 0) {
                computer.id = stoi(line.substr(4));
            } else if (line.find("Name: ") == 0) {
                computer.name = line.substr(6);
            } else if (line.find("Specifications: ") == 0) {
                computer.specs = line.substr(16);
            } else if (line.find("Brand: ") == 0) {
                computer.brand = line.substr(7);
            } else if (line.find("Units: ") == 0) {
                computer.units = stoi(line.substr(7));
            } else if (line == "---") {
                computers.push_back(computer);
            }
        }
        file.close();
    }

private:
    const char* computerPath = "./data/computers.txt";
    vector<Computer> computers;

    int generateID() {
        return computers.empty() ? 1 : computers.back().id + 1;
    }

    void saveComputers() {
        #ifdef _WIN32
        _mkdir("./data");
        #else
        mkdir("./data", 0777);
        #endif

        ofstream file(computerPath);
        if (!file) {
            cout << RED << "Unable to open file." << RESET << endl;
            return;
        }

        for (const auto& computer : computers) {
            file << "ID: " << computer.id << '\n'
                 << "Name: " << computer.name << '\n'
                 << "Specifications: " << computer.specs << '\n'
                 << "Brand: " << computer.brand << '\n'
                 << "Units: " << computer.units << '\n'
                 << "---\n";
        }

        file.close();
    }
};

#endif