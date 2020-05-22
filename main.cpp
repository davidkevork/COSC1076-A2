#include <iostream>
#include <string>
#include <typeinfo>
#include "Menu.h"
#include "Player.h"
#include "BoxLid.h"
#include <vector>
#include "Tile.h"
#include <ctime>

int main(int argc, char* args[]){
    if(std::string(args[1])=="--help"){
        std::cout<<std::endl<<"Usage: Azul.exe [<SEED>]"<<std::endl<<"Seed determines the game's randomness, must be a number."<<std::endl;
    } else if(std::string(args[1])=="--version"){
        std::cout<<std::endl<<"Version 0.1"<<std::endl;
    } else {
        try{
            srand(std::stoi(args[1]));
        } catch (...) {
            srand(std::time(0));
        }
        Menu* menu = new Menu();
        menu->runMenu();
    }
    return EXIT_SUCCESS;
}
