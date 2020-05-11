#ifndef TILE_CONTAINER_H
#define TILE_CONTAINER_H

#include "Tile.h"
#include "Colours.h"

class TileContainer{
    public:
        //Returns true if the tile container contains this specific tile.
        virtual bool contains(Tile* tile);
        //Returns true if the tile container contains a tile of the colour provided.
        virtual bool contains(Colour colour);

        //Removes the specific tile from the container.
        virtual bool remove(Tile* tile);
        //Appends the specific tile to the container.
        virtual bool append(Tile* tile);
};

#endif // TILE_CONTAINER_H
