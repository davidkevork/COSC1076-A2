#include "Tile.h"
#include "Colours.h"

Tile::Tile(Colour colour){
    this->colour = colour;
}

Tile::Tile(std::string colour) {
    if (colour.compare("R") == 0) {
        this->colour = RED;
    } else if (colour.compare("Y") == 0) {
        this->colour = YELLOW;
    } else if (colour.compare("B") == 0) {
        this->colour = LBLUE;
    } else if (colour.compare("D") == 0) {
        this->colour = DBLUE;
    } else if (colour.compare("U") == 0) {
        this->colour = BLACK;
    } else if (colour.compare("F") == 0) {
        this->colour = FIRST_PLAYER;
    }
}

Tile::~Tile(){}


Colour Tile::getColour(){
    return this->colour;
}

std::string Tile::getColourString() {
    std::string colour = "";
    if (this->colour == RED) {
        colour = "R";
    } else if (this->colour == YELLOW) {
        colour = "Y";
    } else if (this->colour == LBLUE) {
        colour = "B";
    } else if (this->colour == DBLUE) {
        colour = "D";
    } else if (this->colour == BLACK) {
        colour = "U";
    } else if (this->colour == FIRST_PLAYER) {
        colour = "f";
    } else {
        colour = "s";
    }
}
