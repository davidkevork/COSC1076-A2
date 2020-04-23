#include <iostream>
#include <string>
#include <typeinfo>
#include "Menu.h"

int main(void) {
    Menu* menu = new Menu();
    menu->runMenu();

    return EXIT_SUCCESS;
}
