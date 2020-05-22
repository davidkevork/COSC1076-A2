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
    std::string args1 = "";
    if (argc > 1) {
        args1 = args[1];
    }
    if(args1.compare("--help") == 0) {
        std::cout<<std::endl<<"Usage: Azul.exe [<SEED>]"<<std::endl<<"Seed determines the game's randomness, must be a number."<<std::endl;
    } else if (args1.compare("--version") == 0) {
        std::cout<<std::endl<<"Version 1.0.0"<<std::endl;
    } else {
        srand(argc > 1 ? std::stoi(args1) : std::time(0));
        Menu* menu = new Menu();
        menu->runMenu();
    }
    return EXIT_SUCCESS;
}
