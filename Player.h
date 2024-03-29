#ifndef PLAYER_H
#define PLAYER_H

#include "Tile.h"
#include <array>
#include <vector>
#include "BoxLid.h"
#include <map>
using std::array;
using std::vector;

class Player{
    public:
        Player(std::string name, BoxLid* boxLid);
        ~Player();
        //Returns players tiles to the box, and applies any outstanding points.
        void nextRound();
        //Calculates final points total for the game and applies it to the players point count.
        void completeGame();
        //Returns the players current score.
        int getScore();
        //True if the player has a complete row of tiles on their wall, signaling the end of the game.
        bool completeRow();
        /**
         * Takes a vector of tiles and tries to place them on a pattern line. Returns false if the move was illegal.
         * This vector may contain the FirstPlayer tile.
         * TODO: Check if that colour is on the wall already in that row as well as checking the pattern wall colour.
         **/
        bool applyTilesToPattern(int patternLine, vector<Tile*> tiles);
        //Transfers tile from pattern line onto the wall. Returns false if the move wasn't valid.
        bool transferTileOntoWall(int patternLine);
        //Returns the tile at the position provided along the wall. Nullptr if none present.
        Tile* getWallTile(int row, int column);
        //Returns the tile at the position provided on the floor. Nullptr if none present.
        Tile* getFloorTile(int index);
        //Returns the tile at the position provided on the the players pattern line. Nullptr if none present.
        Tile* getPatternLineTile(int row, int index);
        //Returns the total points the player has.
        int getPlayerPoints();

        //Sets player points
        void setPlayerPoints(int points);
        
        //Returns the player's name.
        std::string getName();
        //Debug method, prints relevant player details to cout.
        void debug_printAll();
        //Returns a string of the pattern line and tile wall to display to the player.
        std::string toString(int row);
        //Returns a string of the tile floor to display to the player.
        std::string floorToString();

        void appendPatterns(int row, vector<Tile*> tiles);
        void appendMosiac(int row, vector<Tile*> tiles);
        void appendFloor(vector<Tile*> tiles);

        // Outputs patterns in string format to save into file
        std::string patternsToString(int row);
        // Outputs mosiac in string format to save into file
        std::string mosiacToString(int row);

    private: 
        //Add a tile to the players floor. Any tiles that don't fit will be placed back in the bag.
        void addTileToFloor(Tile* tile);
        //Moves tiles left in this pattern line into the box lid.
        void movePatternTilesToBoxLid(int patternLine);
        //Moves all tiles from the floor into the box lid.
        void moveFloorTilesToBoxLid();
        //Moves all tiles from the wall into the box lid.
        void moveWallTilesToBoxLid();

        //Box lid to place tiles into once they are removed from play.
        BoxLid* boxLid;
        //Players name.
        std::string name;
        //Players total points.
        int points;
        //Array of pointers to tiles on the floor.
        Tile** TileFloor;
        //2D array of pointers to tiles on the wall.
        Tile*** TileWall;
        //Array of Pattern line arrays of tile pointers..
        Tile*** PatternLine;
        //Map of all the offsets that each colour uses to determine what coloumn on the mozaic it is on.
        std::map<char, int> colourOffsets;

};

#endif // PLAYER_H
