#ifndef BOX_LID_H
#define BOX_LID_H

#include "TileContainer.h"
#include "TileLList.h"
#include "Colours.h"

/**
 * Object to represent the Azul game's box lid.
 * Tiles are placed here after they are used, before they are placed back into the bag.
 **/
class BoxLid: public TileContainer{
    public:
        BoxLid();
        ~BoxLid();

        bool append(Tile* tile);
        bool remove(Tile* tile);
        bool contains(Tile* tile);
        bool contains(Colour colour);

        std::string toString();
        void moveAllToContainer(TileContainer* container);
    private:
        //Linked list of all tiles in the box.
        TileLList* tiles;
};

#endif // BOX_LID_H
