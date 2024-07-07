#ifndef CUSTOMERADT_H
#define CUSTOMERADT_H

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
    void printError(const string& msg) {
        cerr << "Error: " << msg << endl;
    }
};

void CustomerADT::addCustomer() {
    if (!loadCustomers()) return;

    Customer customer;
    customer.id = getNextID();

    cout << "Enter Customer Name: ";
    getline(cin >> ws, customer.name); 
    cout << "Enter Customer Address: ";
    getline(cin, customer.address);

    customers.push_back(customer);
    saveCustomers();
    cout << "New Customer Added!" << endl;
}

void CustomerADT::showCustomerDetails() {
    if (!loadCustomers()) return;

    int id;
    cout << "Enter Customer ID: ";
    cin >> id;

    bool customerFound = false;
    for (const auto& customer : customers) {
        if (customer.id == id) {
            cout << "ID: " << customer.id << "\nName: " << customer.name << "\nAddress: " << customer.address << endl;
            customerFound = true;
            break;
        }
    }

    if (!customerFound) {
        cout << "Customer ID Not Found!" << endl;
    }
}

void CustomerADT::printAllCustomers() {
    if (!loadCustomers()) return;

    for (const auto& customer : customers) {
        cout << "ID: " << customer.id << "\nName: " << customer.name << "\nAddress: " << customer.address << endl;
    }
}

int CustomerADT::getNextID() {
    return customers.empty() ? 1 : customers.back().id + 1;
}

bool CustomerADT::loadCustomers() {
    ifstream file(customerPath);
    if (!file) {
        printError("Unable to open file: " + string(customerPath));
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
        printError("Unable to open file: " + string(customerPath));
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
