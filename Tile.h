#ifndef TILE_H
#define TILE_H

#include <string>
#include "Colours.h"

/**
 * Tile objects for the Azul game.
 * Each tile has it's own colour.
 **/
class Tile{
    public:
        Tile(Colour colour);
        ~Tile();

        Colour getColour();
    private:
        Colour colour;
};

#endif