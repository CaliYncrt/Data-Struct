#include "computer.h"

void ComputerADT::newComputer() {
    loadComputers();

    Computer computer;
    computer.id = getNextID();

    cout << "Add New Computer\nComputer Name: ";
    getline(cin >> ws, computer.name);
    cout << "Specifications: ";
    getline(cin, computer.specs);
    cout << "Brand: ";
    getline(cin, computer.brand);
    cout << "Number of Units: ";
    cin >> computer.units;

    computers.push_back(computer);
    saveComputers();
    cout << "New Computer Added!" << endl;
}

void ComputerADT::rentComputerByName(const string& name) {
    loadComputers();

    for (auto& computer : computers) {
        if (computer.name == name && computer.units > 0) {
            computer.units--;
            saveComputers();
            return;
        }
    }
}

void ComputerADT::returnComputer() {
    loadComputers();

    string name;
    cout << "Return Computer\nComputer Name: ";
    getline(cin >> ws, name);

    bool computerFound = false;
    for (auto& computer : computers) {
        if (computer.name == name) {
            computer.units++;
            computerFound = true;
            saveComputers();
            cout << "Computer Returned!" << endl;
            break;
        }
    }

    if (!computerFound) {
        cout << "Computer Name Not Found!" << endl;
    }
}

void ComputerADT::showComputerDetails() {
    loadComputers();

    string name;
    cout << "Show Computer Details\nComputer Name: ";
    getline(cin >> ws, name);

    bool computerFound = false;
    for (const auto& computer : computers) {
        if (computer.name == name) {
            displayComputer(computer);
            computerFound = true;
            break;
        }
    }

    if (!computerFound) {
        cout << "Computer Name Not Found!" << endl;
    }
}

void ComputerADT::displayAllComputers() {
    loadComputers();

    for (const auto& computer : computers) {
        displayComputer(computer);
    }
}

bool ComputerADT::checkComputerAvailability(const string& name) {
    loadComputers();

    for (const auto& computer : computers) {
        if (computer.name == name && computer.units > 0) {
            return true;
        }
    }
    return false;
}

const vector<Computer>& ComputerADT::getComputers() const {
    return computers;
}

void ComputerADT::loadComputers() {
    ifstream file(computerPath);
    if (!file) {
        cerr << "Unable to open file: " << computerPath << endl;
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

void ComputerADT::saveComputers() {
    #ifdef _WIN32
    _mkdir("./data");
    #else
    mkdir("./data", 0777);
    #endif

    ofstream file(computerPath);
    if (!file) {
        cerr << "Unable to open file: " << computerPath << endl;
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

int ComputerADT::getNextID() {
    return computers.empty() ? 1 : computers.back().id + 1;
}

void ComputerADT::displayComputer(const Computer& computer) {
    cout << "ID: " << computer.id << "\nName: " << computer.name << "\nSpecifications: " << computer.specs << "\nBrand: " << computer.brand << "\nUnits: " << computer.units << endl;
}
