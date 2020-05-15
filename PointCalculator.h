#ifndef POINT_CALC_H
#define POINT_CALC_H

#include "Tile.h"
class PointCalculator{
    public:
        //Calculates point penalty for a tile on the floor at position.
        static int FloorTile(int position);

        //Calculates point value for placing a tile on the wall at a position.
        static int WallPlacment(Tile*** wall, int tileRow, int tileColumn);

        //Calculates the point value of the wall at the end of the game.
        static int FinalWall(Tile*** wall);

    private:
        static int countConnected(Tile*** wall, int row, int Column, int xMod, int yMod);
};

#endif //POINT_CALC_H
