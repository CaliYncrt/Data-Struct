#ifndef CUSTOMERADT_H
#define CUSTOMERADT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "computer.h"
#include "rent.h"

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

using namespace std;

// Define color codes for text
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

class CustomerADT {
public:
    void addCustomer();
    void showCustomerDetails();
    void printAllCustomers();

private:
    struct Customer {
        int id;
        string name;
        string address;
    };

    const char* customerPath = "./data/customers.txt";
    vector<Customer> customers;

    int getNextID();
    bool loadCustomers();
    void saveCustomers();
    void appendCustomer(const Customer& customer);

    void printError(const string& msg) {
        cerr << RED << "Error: " << RESET << msg << endl;
    }
};

void CustomerADT::addCustomer() {
    if (!loadCustomers()) return;

    Customer customer;
    customer.id = getNextID();

    cout << GREEN << "Enter Customer Name: " << RESET;
    cin.ignore();
    getline(cin, customer.name);
    cout << GREEN << "Enter Customer Address: " << RESET;
    getline(cin, customer.address);

    customers.push_back(customer);
    saveCustomers();
    cout << GREEN << "New Customer Added!" << RESET << endl;
    cin.ignore();
}

void CustomerADT::showCustomerDetails() {
    if (!loadCustomers()) return;

    int id;
    cout << GREEN << "Enter Customer ID: " << RESET;
    cin >> id;

    for (const auto& customer : customers) {
        if (customer.id == id) {
            cout << "ID: " << customer.id << "\nName: " << customer.name << "\nAddress: " << customer.address << endl;
            cin.ignore();
            return;
        }
    }
    cout << RED << "Customer ID Not Found!" << RESET << endl;
    cin.ignore();
}

void CustomerADT::printAllCustomers() {
    if (!loadCustomers()) return;

    for (const auto& customer : customers) {
        cout << "ID: " << customer.id << "\nName: " << customer.name << "\nAddress: " << customer.address << endl;
    }
    cin.ignore();
}

int CustomerADT::getNextID() {
    return customers.empty() ? 1 : customers.back().id + 1;
}

bool CustomerADT::loadCustomers() {
    ifstream file(customerPath);
    if (!file) {
        printError("Unable to open file.");
        return false;
    }

    customers.clear();
    Customer customer;
    string line;
    while (getline(file, line)) {
        if (line.find("ID: ") == 0) {
            customer.id = stoi(line.substr(4));
        } else if (line.find("Name: ") == 0) {
            customer.name = line.substr(6);
        } else if (line.find("Address: ") == 0) {
            customer.address = line.substr(9);
        } else if (line == "---") {
            customers.push_back(customer);
        }
    }
    file.close();
    return true;
}

void CustomerADT::saveCustomers() {
    #ifdef _WIN32
    _mkdir("./data");
    #else
    mkdir("./data", 0777);
    #endif

    ofstream file(customerPath);
    if (!file) {
        printError("Unable to open file.");
        return;
    }

    for (const auto& customer : customers) {
        file << "ID: " << customer.id << '\n'
             << "Name: " << customer.name << '\n'
             << "Address: " << customer.address << '\n'
             << "---\n";
    }

    file.close();
}

#endif