#ifndef TILE_LINKED_LIST_H
#define TILE_LINKED_LIST_H

#include "Tile.h"
#include "TileNode.h"

/**
 * Linked list containing Azul game tiles.
 **/
class TileLList {
    public:
        TileLList();
        ~TileLList();

        //Returns a pointer to a tile at position index in the linked list.
        Tile* getTile(int index);
        //Returns a pointer to the first tile in the linked list.
        Tile* getFirst();
        //Returns a pointer to the last tile in the linked list.
        Tile* getLast();

        /**
         * Inserts a tile into the linked list at a specific position.
         * Returns false if the position is larger than the size of the linked list.
         **/
        bool insert(int position, Tile* tile);
        // Adds a tile to the end of the linked list.
        void append(Tile* tile);
        // size of the linked list
        int size();
        
        /**
         * Removes the tile at the specified position.
         * Returns a pointer to the tile removed (null if none at the position)
         **/
        Tile* remove(int position);
        /**
         * Removes the specified tile from the list.
         * Returns a pointer to the removed tile (null tile was not in list)
         **/
        Tile* remove(Tile* tile);

    private:
        TileNode* head;
        TileNode* tail;
        int _size;

        void setSize(int size);
        void removeTileNode(TileNode* previousNode, TileNode* currentNode);
};

#endif // TILE_LINKED_LIST_H
