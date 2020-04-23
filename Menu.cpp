#include <iostream>
#include "Menu.h"
#include "Credits.h"

using std::cout;
using std::cin;
using std::endl;

Menu::Menu() {
    cout << "Welcome to Azul!" << endl;
    cout << "----------------" << endl;
    cout << endl;
}

Menu::~Menu() {}

void Menu::runMenu() {
    this->choice = 0;

    while(this->choice != 4) {
        this->printMenu();
        cout << "> ";
        cin >> this->choice;
        this->runChoice();
    }
}

void Menu::printMenu() {
    cout << "Menu" << endl;
    cout << "----" << endl;
    cout << "1. New Game" << endl;
    cout << "2. Load Game" << endl;
    cout << "3. Credits (Student Info)" << endl;
    cout << "4. Quit" << endl;
    cout << endl;
}

void Menu::runChoice() {
    if(choice == 1) {
        cout << "running option 1" << endl;
    } else if(choice == 2) {
        cout << "running option 2" << endl;
    } else if(choice == 3) {
        this->credits();
    }
}

void Menu::credits(){
    cout << endl << "Credits:" << endl;
    cout << "--------" << endl;

    Credits* student1 = new Credits("Callum Ackland", "s3791362");
    Credits* student2 = new Credits("Taouit Kiork", "s3815539");
    Credits* student3 = new Credits("Harrison Burr", "s3708981");

    student1->print();
    student2->print();
    student3->print();
}