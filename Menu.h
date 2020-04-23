#ifndef COSC_ASS_TWO_MENU
#define COSC_ASS_TWO_MENU

#include <iostream>
#include <string>

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
};

#endif // COSC_ASS_TWO_MENU
