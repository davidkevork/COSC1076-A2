#ifndef TILE_BAG_H
#define TILE_BAG_H

#include "TileContainer.h"
#include <vector>

class TileBag: public TileContainer{
    private:
        std::vector<Tile*> tiles;
};

#endif // TILE_BAG_H
