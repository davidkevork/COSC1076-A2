#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include "gameEngine.h"

class Menu {
    public:
        Menu();
        ~Menu();

        void runMenu();
        void printMenu();
        void runChoice();
        void credits();

    private:
        int choice;
        gameEngine* ge;
};

#endif // MENU_H
