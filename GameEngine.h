#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <string>
#include <iostream>
#include "Factory.h"
#include "Player.h"
#include "BoxLid.h"
#include "TileBag.h"

using std::string;


/**
 * Azul game engine.
 * Contains the internal game logic.
 **/
class GameEngine{
    public:
        GameEngine();
        //Starts a fresh game.
        void startGame();
        //Resumes a game from a savestate.
        void startGame(std::string saveGame);
        //Performs round with players in player array.
        void round();

        //Save Game
        void saveGame(string fileName);
        //Load Game
        void loadGame(string fileName);

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

        int GameType(string line);
        void loadFactories(string factories, int pos);
        void loadTileBag(string line);
        void loadBoxLid(string line);
        void loadPlayer(string name, string points, int pos);

        vector<string> split(const string splitString, char delimiter);
        string replaceAll(string line, string replace);
};

#endif // GAME_ENGINE_H