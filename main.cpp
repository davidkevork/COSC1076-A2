#include <iostream>
#include <string>
#include <typeinfo>
#include "Menu.h"
#include "Player.h"
#include "BoxLid.h"
#include <vector>
#include "Tile.h"

int main(void) {
    Menu* menu = new Menu();
    menu->runMenu();
    return EXIT_SUCCESS;
}
