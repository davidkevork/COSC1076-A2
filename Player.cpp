#include <string>
#include <vector>
#include <iostream>

#include "Player.h"
#include "Colours.h"
#include "BoardDefinitions.h"
#include "PointCalculator.h"

Player::Player(std::string name, BoxLid* boxLid){
    this->name = name;
    this->points=0;
    this->PatternLine = new Tile**[5];
    for(int row = 0; row < WALL_ROWS; row++){
        this->PatternLine[row] = new Tile*[row+1];
        for(int i = 0; i < row+1; i++){
            this->PatternLine[row][i] = nullptr;
        }
    }
    this->TileWall = new Tile**[5];
    for(int row = 0; row < WALL_ROWS; row++){
        this->TileWall[row] = new Tile*[5];
        for(int column = 0; column< WALL_COLUMNS; column++){
            this->TileWall[row][column] = nullptr;
        }
    }
    this->TileFloor = new Tile*[7];
    for(int i = 0; i < FLOOR_SIZE; i++){
        this->TileFloor[i] = nullptr;
    }
    this->boxLid = boxLid;
}

Player::~Player(){
    //Delete tile wall.
    for(int row = 0; row < WALL_ROWS; row++){
        for(int column = 0; column < WALL_COLUMNS; column++){
            delete this->TileWall[row][column];
        }
        delete[] this->TileWall[row];
    }
    delete[] this->TileWall;

    //Delete pattern lines.
    for(int row = 0; row < WALL_ROWS; row++){
        for(int i = 0; i < row+1; i++){
            delete this->PatternLine[row][i];
        }
        delete[] this->PatternLine[row];
    }
    delete[] this->PatternLine;

    //Delete floor.
    for(int i = 0; i < FLOOR_SIZE; i++){
        delete this->TileFloor[i];
    }
    delete[] this->TileFloor;
}

bool Player::applyTilesToPattern(int row, std::vector<Tile*> tiles){
    bool result = true;
    int rowSpace= row+1;
    for(int i = 0; i < row+1; i++){
        if(this->PatternLine[row][i]!=nullptr){
            rowSpace--;
        }
    }
    if(tiles.at(0)->getColour()==this->PatternLine[row][0]->getColour()){
        result = false;
    }
    if(result){
        for(int i = 0; i < row+1; i++){
            if(this->PatternLine[row][i]==nullptr){
                this->PatternLine[row][i]=tiles.back();
                tiles.pop_back();
            }
        }
        for(Tile* tile:tiles){
            this->addTileToFloor(tile);
        }
    }
    return result;
}

Tile* Player::getFloorTile(int index){
    return this->TileFloor[index];
}

void Player::addTileToFloor(Tile* tile){
    bool added = false;
    for(int i = 0; i < FLOOR_SIZE && !added; i++){
        if(this->TileFloor[i]==nullptr){
            added = true;
            this->TileFloor[i] = tile;
        }
    }
    if(!added){
        this->boxLid->append(tile);
    }
}

Tile* Player::getPatternLineTile(int row, int index){
    return this->PatternLine[row][index];
}

Tile* Player::getWallTile(int row, int column){
    return this->TileWall[row][column];
}

bool Player::completeRow(){
    bool result = false;
    for(int row = 0; row < WALL_ROWS && !result; row++){
        result = true;
        for(int column = 0; column < WALL_COLUMNS; column++){
            if(this->TileWall[row][column]==nullptr){
                result=false;
            }
        }
    }
    return result;
}

void Player::nextRound(){
    //Clear floor.
    for(int i =0 ; i < FLOOR_SIZE; i++){
        if(this->TileFloor[i]!=nullptr){
            this->points+=PointCalculator::FloorTile(i);
            this->boxLid->append(this->TileFloor[i]);
            this->TileFloor[i] = nullptr;
        }
    }
    //Clear pattern line.
    for(int row = 0; row < WALL_ROWS; row++){
        for(int column = 0; column < row+1; column++){
            if(this->PatternLine[row][column]!=nullptr){
                this->boxLid->append(this->PatternLine[row][column]);
                this->PatternLine[row][column] = nullptr;
            }
        }
    }
}

void Player::completeGame(){
    this->points+=PointCalculator::FinalWall(this->TileWall);
    for(int row = 0; row< WALL_ROWS; row++){
        for(int col = 0; col < WALL_COLUMNS; col++){
            this->boxLid->append(this->TileWall[row][col]);
            this->TileWall[row][col] = nullptr;
        }
    }
}