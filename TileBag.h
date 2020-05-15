#ifndef TILE_BAG_H
#define TILE_BAG_H

#include "TileContainer.h"
#include <vector>

class TileBag: public TileContainer{
    public:
        TileBag();
        ~TileBag();

        std::vector<Tile*> getAll();
        Tile* getRandomTile();

        virtual bool contains(Tile* tile);
        virtual bool contains(Colour colour);
        virtual bool append(Tile* tile);
        virtual bool remove(Tile* tile);
    private:
        std::vector<Tile*> tiles;
};

#endif // TILE_BAG_H