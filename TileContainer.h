#ifndef TILE_CONTAINER_H
#define TILE_CONTAINER_H

#include "Tile.h"
#include "Colours.h"

class TileContainer{
    public:
        //We need a deconstructor otherwise g++ won't compile.
        virtual ~TileContainer(){};
        //Returns true if the tile container contains this specific tile.
        virtual bool contains(Tile* tile) = 0;
        //Returns true if the tile container contains a tile of the colour provided.
        virtual bool contains(Colour colour) = 0;

        //Removes the specific tile from the container.
        virtual bool remove(Tile* tile) = 0;
        //Appends the specific tile to the container.
        virtual bool append(Tile* tile) = 0;
};

#endif // TILE_CONTAINER_H