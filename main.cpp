#include <iostream>
#include "adt/computer.h"
#include "adt/customer.h"
#include "adt/rent.h"

using namespace std;

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

int main() {
    int userChoice;
    ComputerADT computerData;
    CustomerADT customerData;
    RentADT rentalData;

    do 
    {
        clearScreen();
        cout << YELLOW << "------------------------------------------------------------" << endl;
        cout << "|                    Computer Rental System                 |" << endl;
        cout << "------------------------------------------------------------" << RESET << endl;
        cout << GREEN << "[1] Add New Computer" << endl;
        cout << "[2] Rent a Computer" << endl;
        cout << "[3] Return a Computer" << endl;
        cout << "[4] Show Computer Details" << endl;
        cout << "[5] Display All Computers" << endl;
        cout << "[6] Check Computer Availability" << endl;
        cout << "[7] Customer Maintenance" << endl;
        cout << "[8] Exit Program" << RESET << endl;
        cout << YELLOW << "------------------------------------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> userChoice;

        switch (userChoice) 
        {
            case 1: {
                clearScreen();
                computerData.getComputers();
                break;
            }
            case 2: {
                clearScreen();
                int customerID;
                string computerName;
                cout << "Enter Customer ID: ";
                cin >> customerID;
                cout << "Enter Computer Name: ";
                cin.ignore();
                getline(cin, computerName);
                rentalData.rentComputer(computerData, customerID, computerName);
                break;
            }
            case 3: {
                clearScreen();
                computerData.returnComputer();
                break;
            }
            case 4: {
                clearScreen();
                computerData.showComputerDetails();
                break;
            }
            case 5: {
                clearScreen();
                computerData.displayAllComputers();
                break;
            }
            case 6: {
                clearScreen();
                cout << "Check Computer Availability\nComputer Name: ";
                cin.ignore();
                string name;
                getline(cin, name);
                if (computerData.checkComputerAvailability(name)) {
                    cout << GREEN << "Computer Available!" << RESET << endl;
                } else {
                    cout << RED << "Computer Not Available!" << RESET << endl;
                }
                cout << "Press enter to continue...";
                cin.ignore();
                break;
            }
            case 7: {
                int userChoice;
                do {
                    clearScreen();
                    cout << YELLOW << "------------------------------------------------------------" << endl;
                    cout << "|                   Customer Maintenance                   |" << endl;
                    cout << "------------------------------------------------------------" << RESET << endl;
                    cout << GREEN << "[1] Add Customer" << endl;
                    cout << "[2] Show Customer Details" << endl;
                    cout << "[3] Print All Customers" << endl;
                    cout << "[4] Return to Main Menu" << endl;
                    cout << "Please make a selection: " << RESET;
                    cin >> userChoice;

                    switch (userChoice) {
                        case 1: {
                            clearScreen();
                            customerData.addCustomer();
                            cin.ignore();
                            cout << "Press enter to continue...";
                            cin.get();
                            break;
                        }
                        case 2: {
                            clearScreen();
                            customerData.showCustomerDetails();
                            cin.ignore();
                            cout << "Press enter to continue...";
                            cin.get();
                            break;
                        }
                        case 3: {
                            clearScreen();
                            customerData.printAllCustomers();
                            cin.ignore();
                            cout << "Press enter to continue...";
                            cin.get();
                            break;
                        }
                        case 4: {
                            break;
                        }
                        default: {
                            cout << RED << "Invalid selection. Try again." << RESET << endl;
                            cin.ignore();
                            cout << "Press enter to continue...";
                            cin.get();
                            break;
                        }
                    }
                } while (userChoice != 4);
                break;
            }
            case 8: {
                clearScreen();
                cout << YELLOW << "Exiting Program." << RESET << endl;
                break;
            }
            default: {
                cout << RED << "Invalid input. Please try again." << RESET << endl;
            }
        }
    } while (userChoice != 8);
}