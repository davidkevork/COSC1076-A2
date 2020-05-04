#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <string>
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

    private:
        //Array containing the games players.
        Player* players[2];
        //Array containing the games factories.
        Factory* Factories[6];
        //Tilebag containing tiles to be placed on factories in the next round.
        TileBag tileBag;
        //BoxLid containing discarded tiles.
        BoxLid boxLid;
};

#endif // GAME_ENGINE_H