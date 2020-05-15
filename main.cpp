#include <iostream>
#include <string>
#include <typeinfo>
#include "Menu.h"
#include "Player.h"
#include "BoxLid.h"
#include <vector>
#include "Tile.h"

int main(void) {
    //Menu* menu = new Menu();
    //menu->runMenu();
    BoxLid boxLid = BoxLid();
    Player player = Player("Jeff", &boxLid);
    std::vector<Tile*> tiles;
    Tile* red1 = new Tile(RED);
    tiles.push_back(red1);
    Tile* red2 = new Tile(RED);
    tiles.push_back(red2);
    Tile* red3 = new Tile(RED);
    tiles.push_back(red3);
    Tile* red4 = new Tile(RED);
    tiles.push_back(red4);
    Tile* red5 = new Tile(RED);
    tiles.push_back(red5);
    std::cout<<player.applyTilesToPattern(0, tiles);
    std::cout<<player.applyTilesToPattern(1, tiles);
    std::cout<<player.applyTilesToPattern(2, tiles);
    std::cout<<player.applyTilesToPattern(3, tiles);
    std::cout<<player.applyTilesToPattern(4, tiles)<<std::endl;
    std::cout<<player.transferTileOntoWall(0);
    std::cout<<player.transferTileOntoWall(1);
    std::cout<<player.transferTileOntoWall(2);
    std::cout<<player.transferTileOntoWall(3);
    std::cout<<player.transferTileOntoWall(4)<<std::endl;
    player.nextRound();
    player.debug_printAll();
    return EXIT_SUCCESS;
}
