#ifndef TILE_NODE_H
#define TILE_NODE_H

#include "Tile.h"

/**
 * @brief
 * Data structure for nodes in the TileLList.
 * Each node contains a pointer to it's tile
 * and a pointer to the next tile in the linked list.
 */
class TileNode
{
    public:
        /**
         * @brief Construct a new Tile Node object
         * 
         * @param tile The Tile object to store
         * @param next The next tile node in the list
         */
        TileNode(Tile* tile, TileNode* next);
        /**
         * @brief Construct a new Tile Node object from another tile node
         * 
         * @param other Other tile node to copy from
         */
        TileNode(TileNode* other);
        /**
         * @brief Construct a new Tile Node object from another tile node
         * 
         * @param other Other tile node to copy from
         */
        TileNode(TileNode&& other);
        /**
         * @brief Destroy the Tile Node object
         */
        ~TileNode();

        /**
         * @brief Get the Tile object
         * 
         * @return Tile* Tile object
         */
        Tile* getTile();
        /**
         * @brief Set the Tile object
         * 
         * @param self The new Tile object
         */
        void setTile(Tile* self);

        /**
         * @brief Get the Next object
         * 
         * @return TileNode* Next tile node
         */
        TileNode* getNext();
        /**
         * @brief Set the Next object
         * 
         * @param next The next tile node
         */
        void setNext(TileNode* next);
    private:
        /**
         * @brief Tile object which this linked list node references
         */
        Tile* tile;
        /**
         * @brief Pointer to the next tile node in the linked list
         */
        TileNode* next;
};

#endif // TILE_NODE_H
