#include "Menu.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

Menu::Menu() {
    cout << "Welcome to Azul!" << endl;
    cout << "----------------" << endl;
    cout << endl;
}

void Menu::runMenu(){
    this->choice = 0;

    while(this->choice != 4){
        Menu::printMenu();
        cout << "> ";
        cin >> this->choice;
        Menu::runChoice();
    }

}

void Menu::printMenu(){
    cout << "Menu" << endl;
    cout << "----" << endl;
    cout << "1. New Game" << endl;
    cout << "2. Load Game" << endl;
    cout << "3. Credits (Student Info)" << endl;
    cout << "4. Quit" << endl;
    cout << endl;
}

void Menu::runChoice(){
    if(choice == 1){
        cout << "running option 1" << endl;
    }else if(choice == 2){
        cout << "running option 2" << endl;
    }else if(choice == 3){
        Menu::credits();
    }
}

void Menu::credits(){
    cout << endl << "Credits:" << endl;
    cout << "--------" << endl;

    cout << "1:" << endl << "Name: Callum Ackland" << endl << "Student ID: s3791362" << endl 
    << "Email: s3791362@student.rmit.edu.au" << endl;
    cout << endl;
    cout << "2:" << endl << "Taouit Kiork - []" << endl;
    cout << endl;
    cout << "3:" << endl << "Harrison Burr - []" << endl;
    cout << endl;
}