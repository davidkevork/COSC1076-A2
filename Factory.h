#ifndef FACTORY_H
#define FACTORY_H

#include <vector>
#include "Tile.h"
#include "Colours.h"
#include "TileContainer.h"
/**
 * Factory object for the Azul game.
 * Factories contain tiles that the players can collect.
 **/
class Factory: public TileContainer{
    public:
        Factory();
        ~Factory();

        //Get pointers to all tiles in the factory.
        std::vector<Tile*> getAll();
        //Get pointers to all tiles of a specific colour in the factory.
        std::vector<Tile*> getAll(Colour colour);

        //Shifts all tiles from this factory into the specified factory.
        void moveToFactory(Factory* factory);

        //Shifts all tiles to a new tileContainer
        void moveToContainer(TileContainer* container);
        
        //Returns the number of tiles in the factory.
        int getSize();

        //Returns true if this->getSize() = 0; 
        bool isEmpty();

        //Returns a string for displaying what tiles are in the factory.
        std::string toString();
    private:
        //Vector containing pointers to all tiles in the factory.
        std::vector<Tile*> tiles;
};

#endif // FACTORY_H
