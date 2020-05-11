#include "Tile.h"
#include "Colours.h"

Tile::Tile(Colour colour){
    this->colour = colour;
}

Tile::~Tile(){}


Colour Tile::getColour(){
    return this->colour;
}
