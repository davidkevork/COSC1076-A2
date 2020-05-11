#ifndef BOX_LID_H
#define BOX_LID_H

#include "TileContainer.h"
#include "TileLList.h"
/**
 * Object to represent the Azul game's box lid.
 * Tiles are placed here after they are used, before they are placed back into the bag.
 **/
class BoxLid: public TileContainer{
    public:
        BoxLid();
        ~BoxLid();
    private:
        //Linked list of all tiles in the box.
        TileLList* tiles;
};

#endif // BOX_LID_H
