#include <string>
#include <vector>
#include <iostream>
#include <map>

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

    //Set up the offsets for each colour.
    this->colourOffsets[DBLUE]  =0;
    this->colourOffsets[YELLOW] =1;
    this->colourOffsets[RED]    =2;
    this->colourOffsets[BLACK]  =3;
    this->colourOffsets[LBLUE]  =4;
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
    if(this->PatternLine[row][0]!=nullptr){
        if(tiles.at(0)->getColour()==this->PatternLine[row][0]->getColour()){
            result = false;
        }
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
    //Calculate points penalty from floor tiles.
    for(int pos = 0; pos < FLOOR_SIZE; pos++){
        if(this->TileFloor[pos]!=nullptr){
            this->points+=PointCalculator::FloorTile(pos);
        }
    }
    //Clear floor tiles.
    this->moveFloorTilesToBoxLid();
    //Clear anything left in pattern lines.
    for(int row = 0; row < WALL_ROWS; row++){
        this->movePatternTilesToBoxLid(row);
    }
}

void Player::completeGame(){
    this->points+=PointCalculator::FinalWall(this->TileWall);
    this->moveFloorTilesToBoxLid();
    this->moveWallTilesToBoxLid();
    for(int row = 0; row < WALL_ROWS; row++){
        this->movePatternTilesToBoxLid(row);
    }
}
int Player::getPlayerPoints(){
    return this->points;
}

bool Player::transferTileOntoWall(int patternLine){
    bool result = true;
    //Check that pattern line is full.
    for(int col = 0; col < patternLine+1; col++){
        if(this->PatternLine[patternLine][col]==nullptr){
            result=false;
        }
    }
    Tile* tileToMove = this->PatternLine[patternLine][0];
    int wallColumn = (patternLine+this->colourOffsets[tileToMove->getColour()])%5;
    //Check that the colour spot on the wall is free.
    if(this->TileWall[patternLine][wallColumn]!=nullptr){
        result = false;
    }
    //Place tile on wall.
    if(result){
        this->TileWall[patternLine][wallColumn] = this->PatternLine[patternLine][0];
        this->PatternLine[patternLine][0] = nullptr;
        //Shift any remaining tiles into the boxlid
        this->movePatternTilesToBoxLid(patternLine);
    }
    return result;
}

void Player::movePatternTilesToBoxLid(int patternLine){
    for(int col = 0; col < (patternLine+1); col++){
        if(this->PatternLine[patternLine][col]!=nullptr){
            this->boxLid->append(this->PatternLine[patternLine][col]);
            this->PatternLine[patternLine][col]=nullptr;
        }
    }
}

void Player::moveFloorTilesToBoxLid(){
    for(int i = 0; i < FLOOR_SIZE; i++){
        if(this->TileFloor[i]!=nullptr){
            this->boxLid->append(this->TileFloor[i]);
            this->TileFloor[i] = nullptr;
        }
    }
}

void Player::moveWallTilesToBoxLid(){
    for(int row = 0; row < WALL_ROWS; row++){
        for(int col = 0; col < WALL_COLUMNS; col++){
            if(this->TileWall[row][col]!=nullptr){
                this->boxLid->append(this->TileWall[row][col]);
                this->TileWall[row][col]=nullptr;
            }
        } 
    }
}

void Player::debug_printAll(){
    std::cout<<"Points:"<<this->points<<std::endl;
    std::cout<<"Wall"<<std::endl;
    for(int row = 0; row < WALL_ROWS; row++){
        for(int col = 0; col < WALL_COLUMNS; col++){
            std::cout<<this->TileWall[row][col] << ". ";
        }
        std::cout<<std::endl;
    }
    std::cout<<"Pattern Lines"<<std::endl;
    for(int row = 0; row < WALL_ROWS; row++){
        for(int col = 0; col <(row+1); col++){
            std::cout<<this->PatternLine[row][col] << ". ";
        }
        std::cout<<std::endl;
    }
    std::cout<<"Floor"<<std::endl;
    for(int i = 0; i < FLOOR_SIZE; i++){
        std::cout<<this->TileFloor[i]<<". ";
    }

}

std::string Player::getName() {
    return this->name;
}