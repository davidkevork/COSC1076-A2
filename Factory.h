#include <vector>
#include "Tile.h"
#include "Colours.h"

class Factory: Tile{
    public:
        Factory();

        bool contains(Tile);

        std::vector<Tile> getAll();

        Tile* getFront();
        Tile* getBack();
        Tile* getAt(int index);

        Tile* append(Tile* tile);
        void remove(Tile* tile);

        int getSize();
    private:
        std::vector<Tile> tiles;
        
};