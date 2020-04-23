#include <iostream>
#include <string>
#include "Menu.cpp"
#include <typeinfo>

int main(void) {
    Menu *menu = new Menu();
    menu->runMenu();

    return EXIT_SUCCESS;
}