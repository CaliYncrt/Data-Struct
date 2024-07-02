#include <iostream>
#include "adt/computer.h"
#include "adt/customer.h"
#include "adt/rent.h"

using namespace std;

void clrscr() {
    cout << "\033[2J\033[1;1H";
}

int main() {
    int choice;
    ComputerADT myComputer;
    CustomerADT myCustomer;
    RentADT myRental;

    do {
        clrscr();
        cout << "[1] Add New Computer" << endl;
        cout << "[2] Rent a Computer" << endl;
        cout << "[3] Return a Computer" << endl;
        cout << "[4] Show Computer Details" << endl;
        cout << "[5] Display All Computers" << endl;
        cout << "[6] Check Computer Availability" << endl;
        cout << "[7] Customer Maintenance" << endl;
        cout << "[8] Exit Program" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                clrscr();
                myComputer.newComputer();
                break;
            }
            case 2: {
                clrscr();
                int customerId;
                string computerName;
                cout << "Enter Customer ID: ";
                cin >> customerId;
                cout << "Enter Computer Name: ";
                cin.ignore();
                getline(cin, computerName);
                myRental.rentComputer(myComputer, customerId, computerName);
                break;
            }
            case 3: {
                clrscr();
                myComputer.returnComputer();
                break;
            }
            case 4: {
                clrscr();
                myComputer.showComputerDetails();
                break;
            }
            case 5: {
                clrscr();
                myComputer.displayAllComputers();
                break;
            }
            case 6: {
                clrscr();
                cout << "Check Computer Availability\nComputer Name: ";
                cin.ignore();
                string name;
                getline(cin, name);
                if (myComputer.checkComputerAvailability(name)) {
                    cout << "Computer Available!" << endl;
                } else {
                    cout << "Computer Not Available!" << endl;
                }
                cout << "Press enter to continue...";
                cin.ignore();
                break;
            }
            case 7: {
                clrscr();
                cout << "[1] Add Customer" << endl;
                cout << "[2] Show Customer Details" << endl;
                cout << "[3] Print All Customers" << endl;
                cout << "Enter your choice: ";
                int subChoice;
                cin >> subChoice;
                switch (subChoice) {
                    case 1:
                        myCustomer.addCustomer();
                        break;
                    case 2:
                        myCustomer.showCustomerDetails();
                        break;
                    case 3:
                        myCustomer.printAllCustomers();
                        break;
                    default:
                        cout << "Invalid input. Please try again." << endl;
                }
                break;
            }
            case 8: {
                clrscr();
                cout << "Exiting Program." << endl;
                break;
            }
            default:
                cout << "Invalid input. Please try again." << endl;
        }

        cin.ignore();
    } while (choice != 8);

    return 0;
}
