#include <iostream>
#include <string>
#include <typeinfo>
#include "Menu.h"
#include "Player.h"
#include "BoxLid.h"
#include <vector>
#include "Tile.h"
#include <ctime>

int main(int argc, char* args[]) {
    Menu* menu = new Menu();
    try{
        srand(std::stoi(args[1]));
    } catch (...) {
        srand(std::time(0));
    }
    menu->runMenu();
    return EXIT_SUCCESS;
}
