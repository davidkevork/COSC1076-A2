#ifndef PLAYER_H
#define PLAYER_H

#include "Tile.h"
#include <array>
#include <vector>
using std::array;
using std::vector;

class Player{
    public:
        Player(std::string name);
        ~Player();

        //Returns players tiles to the box, and applies any outstanding points.
        void nextRound();

        //True if the player has a complete row of tiles on their wall (NOT ON A PATTERN LINE)
        bool completeRow();

        /**
         * Takes a vector of tiles and tries to place them on a pattern line. Returns false if the move was illegal.
         * This vector may contain the FirstPlayer tile.
         **/
        bool applyTiles(int patternLine, vector<Tile*> tiles);

        //Returns the tile at the position provided along the wall. Nullptr if none present.
        Tile* getWallTile(int row, int column);

        //Returns the tile at the position provided on the floor. Nullptr if none present.
        Tile* getFloorTile(int index);

        //Returns the tile at the position provided on the the players pattern line. Nullptr if none present.
        Tile* getPatternLineTile(int row, int index);

    private: 
        //Players name.
        std::string name;
        //Players total points.
        int points;
        //Array of tiles on the floor.
        Tile** TileFloor[7];
        //2D array of tiles on the wall.
        Tile** TileWall[5][5];
        //Array of pattern line arrays.
        Tile** PatternLine[5];
};

#endif // PLAYER_H
