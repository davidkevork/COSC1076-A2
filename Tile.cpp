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
