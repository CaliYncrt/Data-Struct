#include <iostream>
#include <limits>
#include "adt/computer.h"
#include "adt/customer.h"
#include "adt/rent.h"

using namespace std;

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void displayMainMenu() {
    cout << "-----------------------------" << endl;
    cout << "       COMPUTER SHOP         " << endl;
    cout << "-----------------------------" << endl;
    cout << "[1] Add New Computer" << endl;
    cout << "[2] Rent a Computer" << endl;
    cout << "[3] Return a Computer" << endl;
    cout << "[4] Show Computer Details" << endl;
    cout << "[5] Display All Computers" << endl;
    cout << "[6] Check Computer Availability" << endl;
    cout << "[7] Customer Maintenance" << endl;
    cout << "[8] Exit Program" << endl;
}

int getUserChoice(int min, int max) {
    int choice;
    while (true) {
        cout << "Enter your choice (" << min << " - " << max << "): ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (choice < min || choice > max) {
            cout << "Invalid choice. Please enter a number between " << min << " and " << max << "." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
    }
}

void waitForEnter() {
    cout << "Press enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void executeMainMenuChoice(int choice, ComputerADT& myComputer, CustomerADT& myCustomer, RentADT& myRental) {
    clearScreen();
    switch (choice) {
        case 1:
            myComputer.newComputer();
            break;
        case 2: {
            int customerId;
            string computerName;
            cout << "Enter Customer ID: ";
            cin >> customerId;
            cout << "Enter Computer Name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, computerName);
            myRental.rentComputer(myComputer, customerId, computerName);
            break;
        }
        case 3:
            myComputer.returnComputer();
            break;
        case 4:
            myComputer.showComputerDetails();
            break;
        case 5:
            myComputer.displayAllComputers();
            break;
        case 6: {
            string name;
            cout << "Check Computer Availability\nComputer Name: ";
            getline(cin, name);
            if (myComputer.checkComputerAvailability(name)) {
                cout << "Computer Available!" << endl;
            } else {
                cout << "Computer Not Available!" << endl;
            }
            waitForEnter();
            break;
        }
        case 7: {
            int customerChoice;
            do {
                clearScreen();
                cout << "[1] Add Customer" << endl;
                cout << "[2] Show Customer Details" << endl;
                cout << "[3] Print All Customers" << endl;
                cout << "[4] Return to Main Menu" << endl;
                cout << "Please make a selection: ";
                customerChoice = getUserChoice(1, 4);

                switch (customerChoice) {
                    case 1:
                        clearScreen();
                        myCustomer.addCustomer();
                        waitForEnter();
                        break;
                    case 2:
                        clearScreen();
                        myCustomer.showCustomerDetails();
                        waitForEnter();
                        break;
                    case 3:
                        clearScreen();
                        myCustomer.printAllCustomers();
                        waitForEnter();
                        break;
                    case 4:
                        break;
                    default:
                        cout << "Invalid selection. Try again." << endl;
                        waitForEnter();
                        break;
                }
            } while (customerChoice != 4);
            break;
        }
        case 8:
            cout << "Exiting Program." << endl;
            break;
        default:
            cout << "Invalid input. Please try again." << endl;
            waitForEnter();
            break;
    }
}

int main() {
    int choice;
    ComputerADT myComputer;
    CustomerADT myCustomer;
    RentADT myRental;

    do {
        clearScreen();
        displayMainMenu();
        choice = getUserChoice(1, 8);
        executeMainMenuChoice(choice, myComputer, myCustomer, myRental);
    } while (choice != 8);

    return 0;
}
