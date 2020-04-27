#include "Tile.h"

class TileLList{
    public:
        TileLList();
        ~TileLList();

        Tile* getTile(int index);
        Tile* getFirst();
        Tile* getLast();

        //Inserts so the tile is at the tile is at index n, the new tile will point to the old tile at n if any..
        bool insert(int position, Tile* tile);
        void append(Tile* tile);
        
        Tile* remove(int position);
        Tile* remove(Tile* tile);

    private:
        tileNode* start;
};

struct tileNode{
    public:
        Tile* self;
        Tile* next;
};