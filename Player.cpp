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
    this->TileFloor = new Tile*[FLOOR_SIZE];
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

int Player::getScore(){
    return this->points;
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
        if(tiles.at(0)->getColour()!=this->PatternLine[row][0]->getColour()){
            result = false;
        }
        //Check that the colour spot on the wall is free.
    }
    //Check if the space on the wall this tile will occupy is free.
    if(tiles.back()->getColour()!=FIRST_PLAYER){
        int wallColumn = (row+this->colourOffsets[tiles.back()->getColour()])%5;
        if(this->TileWall[row][wallColumn]!=nullptr){
            result = false;
        }
    } else if(tiles.front()->getColour()!=FIRST_PLAYER){
        int wallColumn = (row+this->colourOffsets[tiles.front()->getColour()])%5;
        if(this->TileWall[row][wallColumn]!=nullptr){
            result = false;
        }
    } else{
        //This will only happen if the only tile you try and pick up is a FIRST_PLAYER token.
        result = false;
    }   
    if(result){
        for(int i = 0; i < row+1; i++){
            if(this->PatternLine[row][i]==nullptr && tiles.size()!=0){
                if(tiles.back()->getColour()==FIRST_PLAYER){
                    this->addTileToFloor(tiles.back());
                    tiles.pop_back();
                } else{
                    this->PatternLine[row][i]=tiles.back();
                    tiles.pop_back();
                }
            }
        }
        for(Tile* tile:tiles){
            this->addTileToFloor(tile);
        }
    }
    return result;
}

Tile* Player::getFloorTile(int index) {
    Tile* tile = nullptr;
    if (index < FLOOR_SIZE && index > 0 && this->TileFloor != nullptr) {
        tile = this->TileFloor[index];
    }
    return tile;
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

void Player::setPlayerPoints(int points) {
    this->points = points;
}

bool Player::transferTileOntoWall(int patternLine){
    int wallColumn = 0;
    bool result = true;
    //Check that pattern line is full.
    for(int col = 0; col < patternLine+1; col++){
        if(this->PatternLine[patternLine][col]==nullptr){
            result=false;
        }
    }
    //Check that the colour spot on the wall is free.
    if(result){
        Tile* tileToMove = this->PatternLine[patternLine][0];
        wallColumn = (patternLine+this->colourOffsets[tileToMove->getColour()])%5;
        if(this->TileWall[patternLine][wallColumn]!=nullptr){
            result = false;
        }
    }
    //Place tile on wall.
    if(result){
        this->TileWall[patternLine][wallColumn] = this->PatternLine[patternLine][0];
        this->PatternLine[patternLine][0] = nullptr;
        //Shift any remaining tiles into the boxlid
        this->movePatternTilesToBoxLid(patternLine);
    }
    //Add points for the placement.
    this->points+=PointCalculator::WallPlacment(this->TileWall, patternLine, wallColumn);
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

std::string Player::getName() {
    return this->name;
}

std::string Player::toString(int row){
    std::string result = "";
    //Add negative space.
    for(int i = 0; i < (4-row); i++){
        result = result+"  ";
    }
    //Add pattern lines.
    for(int col = row; col >= 0; col--){
        if(this->PatternLine[row][col]!=nullptr){
            result = result+this->PatternLine[row][col]->getColour() + " ";
        } else {
            result = result+". ";
        }
        
    }
    //Add spacer.
    result = result+"|| ";
    //Add tile wall.
    for(int col = 0; col < WALL_COLUMNS; col++){
        if(this->TileWall[row][col]!=nullptr){
            result = result+this->TileWall[row][col]->getColour() + " ";
        } else {
            result = result+". ";
        }
    }
    return result;
}

std::string Player::floorToString(){
    std::string result = "";
    for(int i = 0; i < FLOOR_SIZE; i++){
        if(this->TileFloor[i]!=nullptr){
            result = result + this->TileFloor[i]->getColour() + " ";
        }else if(this->TileFloor[i]==nullptr){
            result = result + "." + " ";
        }
    }
    if (result.size() > 0) {
        result.pop_back();
    }
    return result;
}

void Player::appendPatterns(int row, vector<Tile*> tiles) {
    for (unsigned int i = 0; i < tiles.size(); i++) {
        this->PatternLine[row][i] = tiles[i];
    }
}

void Player::appendMosiac(int row, vector<Tile*> tiles) {
    for (unsigned int i = 0; i < tiles.size(); i++) {
        this->TileWall[row][i] = tiles[i];
    }
}
void Player::appendFloor(vector<Tile*> tiles) {
    for (unsigned int i = 0; i < tiles.size(); i++) {
        this->TileFloor[i] = tiles[i];
    }
}

std::string Player::patternsToString(int row) {
    std::string result = "";
    //Add pattern lines.
    for(int col = row; col >= 0; col--){
        if(this->PatternLine[row][col] != nullptr){
            result = result + this->PatternLine[row][col]->getColour() + " ";
        } else {
            result = result + ". ";
        }   
    }
    if (result.size() > 0) {
        result.pop_back();
    }
    return result;
}

std::string Player::mosiacToString(int row) {
    std::string result = "";
    //Add tile wall.
    for(int col = 0; col < WALL_COLUMNS; col++){
        if(this->TileWall[row][col] != nullptr){
            result = result + this->TileWall[row][col]->getColour() + " ";
        } else {
            result = result + ". ";
        }
    }
    if (result.size() > 0) {
        result.pop_back();
    }
    return result;
}
