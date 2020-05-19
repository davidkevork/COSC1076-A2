#include "Tile.h"
#include "BoardDefinitions.h"
#include "PointCalculator.h"
#include <map>
#include <vector>

int PointCalculator::FloorTile(int position){
    int result = 0;
    if(position <= 1){
        result = -1;
    } else if(position <= 3){
        result = -2;
    } else { 
        result = -3;
    }
    return result;
}

int PointCalculator::countConnected(Tile*** wall, int row, int column, int rowMod, int colMod){
    bool valid = true;
    int result = 0;
    if(row+rowMod < 0 || column+colMod < 0){
        //Coord out of bounds.
        valid = false;
    }
    if(row+rowMod >= WALL_ROWS || column+colMod >= WALL_COLUMNS){
        //Coord out of bounds.
        valid = false;
    }
    if(valid){
        if(wall[row+rowMod][column+colMod]!=nullptr){
            //Check for any times connected in the same direction.
            result+=countConnected(wall, row+rowMod, column+colMod, rowMod, colMod);
            //Add 1 for this tile.
            result+=1;
        }
    }
    return result;
}

int PointCalculator::WallPlacment(Tile*** wall, int tileRow, int tileColumn){

    int hPoints = 0;
    int vPoints = 0;
    //Count above.
    vPoints+= countConnected(wall, tileRow, tileColumn, +1, 0);
    //Count below.
    vPoints+= countConnected(wall, tileRow ,tileColumn, -1, 0);
    //Count left.
    hPoints+= countConnected(wall, tileRow, tileColumn, 0, -1);
    //Count right.
    hPoints+= countConnected(wall, tileRow, tileColumn, 0, +1);

    if(hPoints!=0){
        hPoints++;
    }
    if(vPoints!=0){
        vPoints++;
    }
    int totalPoints = hPoints+vPoints;
    if(totalPoints==0){
        totalPoints=1;
    } 
    return totalPoints;
}

int PointCalculator::FinalWall(Tile*** wall){
    int points = 0;
    //Count full rows.
    for(int row = 0; row < WALL_ROWS; row++){
        if(countConnected(wall, row, -1, 0, +1)==5){
            points+=2;
        }
    }
    //Count full columns.
    for(int column = 0; column < WALL_COLUMNS; column++){
        if(countConnected(wall, -1, column, +1, 0)==5){
            points+=7;
        }
    }
    //Count if 5 tiles of a particular colour are on the board.
    std::vector<char> colourList;
    colourList.push_back(RED);
    colourList.push_back(YELLOW);
    colourList.push_back(LBLUE);
    colourList.push_back(DBLUE);
    colourList.push_back(BLACK);

    std::map<char, int> colourCounts;
    for(Colour colour:colourList){
        colourCounts[colour]=0;
    }

    for(int row = 0; row < WALL_ROWS; row++){
        for(int column = 0; column < WALL_COLUMNS; column++){
            if(wall[row][column]!=nullptr){
                colourCounts[wall[row][column]->getColour()]+=1;
            }
        }
    }    

    for(Colour colour:colourList){
        if(colourCounts[colour]==5){
            points+=10;
        }
    }

    return points;
}
