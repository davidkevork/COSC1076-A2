#include <iostream>
#include <string>
#include "Menu.h"
#include "Credits.h"
#include "GameEngine.h"

using std::cout;
using std::cin;
using std::endl;

Menu::Menu() {
    cout << "Welcome to Azul!" << endl;
    cout << "----------------" << endl;
    cout << endl;
    this->ge = new GameEngine();
}

Menu::~Menu() {}

void Menu::runMenu() {
    this->choice = 0;

    while(this->choice != 4) {
        this->printMenu();
        cout << "> ";
        cin>>this->choice;
        //Removes the trailing \n from cin.
        std::string catcher;
        std::getline(cin, catcher);
        
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
        cout << endl<< "Starting a New Game" << endl << endl;
        this->ge->startGame();
    } else if(choice == 2) {
        cout << endl<< "Enter File:" << endl << endl;
        std::string saveGame = "";
        cin >> saveGame;
        this->ge->startGame(saveGame);
    } else if(choice == 3) {
        this->credits();
    } else if(choice == 4){
        cout << "Goodbye!" << endl;
        this->choice = 4;
    } else if(cin.eof()) {
        cout << "Goodbye!" << endl;
        this->choice = 4;
    }else {
        cout << "Invalid Input" << endl;
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