#ifndef TILE_H
#define TILE_H

#include <string>
#include "Colours.h"

class Tile{
    public:
        Tile(Colour colour);
        ~Tile();

        Colour getColour();
    private:
        Colour colour;
};

#endif