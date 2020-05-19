#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <string>
#include <iostream>
#include "Factory.h"
#include "Player.h"
#include "BoxLid.h"
#include "TileBag.h"


/**
 * Azul game engine.
 * Contains the internal game logic.
 **/
class gameEngine{
    public:
        gameEngine();
        //Starts a fresh game.
        void startGame();
        //Resumes a game from a savestate.
        void startGame(std::string saveGame);
        //Performs round with players in player array.
        void round(int startingPlayer);

    private:
        //Array containing the games players.
        Player* players[2];
        //Array containing the games factories.
        Factory* factories[6];
        //Tilebag containing tiles to be placed on factories in the next round.
        TileBag* tileBag;
        //BoxLid containing discarded tiles.
        BoxLid* boxLid;
        //Round number
        int roundno;
        //Returns true if any of the players have won the game, otherwise false.
        bool checkGameFinsihed();
        //Returns true if each factory is empty, otherwise false.
        bool checkFactoriesEmpty();
        //Removes the first player token from the tilebag and boxlid, and places it into the center factory.
        void resetFirstPlayerToken();
        //Pointer to the first player token.
        Tile* firstPlayerToken;

        std::vector<std::string> getPlayerTurnCommand();

        bool quitGameFlag;
};


#endif // GAME_ENGINE_H