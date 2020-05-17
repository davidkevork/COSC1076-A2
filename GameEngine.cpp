#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "GameEngine.h"
#include "Tile.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

GameEngine::GameEngine() {
    Factory* fac0 = new Factory();
    Factory* fac1 = new Factory();
    Factory* fac2 = new Factory();
    Factory* fac3 = new Factory();
    Factory* fac4 = new Factory();
    Factory* fac5 = new Factory();
    this->factories[0] = fac0;
    this->factories[1] = fac1;
    this->factories[2] = fac2;
    this->factories[3] = fac3;
    this->factories[4] = fac4;
    this->factories[5] = fac5;

    this->tileBag = new TileBag();
    this->boxLid = new BoxLid();
}

void GameEngine::startGame() {
    //Player 1 Creation
    string player1name;
    cout << "Enter a name for player 1" << endl;
    cout << "> ";
    cin >> player1name;
    Player* player1 = new Player(player1name, this->boxLid);
    cout << endl;
    //Player 2 Creation
    string player2name;
    cout << "Enter a name for player 2" << endl;
    cout << "> ";
    cin >> player2name;
    Player* player2 = new Player(player2name, this->boxLid);
    cout << endl;

    this->players[0] = player1;
    this->players[1] = player2;

    cout << "Let's Play!" << endl << endl;
    round();

}

void GameEngine::startGame(string saveGame) {

}

void GameEngine::round() {
    cout << "=== Start Round "<< this->roundno << " ===" << endl;
    for(Player* player : this->players) {
        cout << "TURN FOR PLAYER: " << player->getName() << endl << endl;
    }
}

void GameEngine::saveGame() {
    std::ofstream saveFile("save");
    // saveFile.open('./save');
}

void GameEngine::loadGame() {
    std::ifstream saveFile("save");

    if (saveFile.good()) {
        while (!saveFile.eof()) {
            string line;
            std::getline(saveFile, line);
            int gameType = this->GameType(line);
            if (gameType == 1) {
                std::getline(saveFile, line);
                this->loadFactories(line, 0);
                std::getline(saveFile, line);
                this->loadFactories(line, 1);
                std::getline(saveFile, line);
                this->loadFactories(line, 2);
                std::getline(saveFile, line);
                this->loadFactories(line, 3);
                std::getline(saveFile, line);
                this->loadFactories(line, 4);
                std::getline(saveFile, line);
                this->loadFactories(line, 5);
            } else if (gameType == 2) {
                this->loadTileBag(line);
            } else if (gameType == 3) {
                this->loadBoxLid(line);
            }
        }
    }
}

vector<string> GameEngine::split(const string splitString, char delimiter) {
    vector<string> out;
    std::stringstream stringStream (splitString);
    string item;
    while (getline(stringStream, item, delimiter)) {
        out.push_back(item);
    }
    return out;
}

string GameEngine::replaceAll(string line, string replace) {
    string data = line;
	int pos = data.find(replace);
	while(pos != string::npos) {
		data.replace(pos, replace.size(), "");
		pos = data.find(replace, pos);
	}
    return data;
}

void GameEngine::loadTileBag(string line) {
    vector<string> tileBagString = this->split(this->replaceAll(line, "// Tile Bag"), ' ');
    for (string colour : tileBagString) {
        (*this->tileBag).append(new Tile(colour));
    }
}

void GameEngine::loadBoxLid(string line) {
    vector<string> boxLidString = this->split(this->replaceAll(line, "// Box Lid"), ' ');
    for (string colour : boxLidString) {
        (*this->boxLid).append(new Tile(colour));
    }
}


void GameEngine::loadFactories(string factories, int pos) {
    vector<string> splitString = this->split(factories, ' ');
    for (string colour : splitString) {
        (*this->factories[pos]).append(new Tile(colour));
    }
}

int GameEngine::GameType(string line) {
    if (line.find("// game state data") != string::npos) {
        return 1;
    } else if (line.find("// Tile Bag") != string::npos) {
        return 2;
    } else if (line.find("// Box Lid") != string::npos) {
        return 3;
    } else if (line.find("// player 1 save data") != string::npos) {
        return 4;
    } else if (line.find("// player 2 save data") != string::npos) {
        return 5;
    } else if (line.find("// Player 1 Patterns") != string::npos) {
        return 6;
    } else if (line.find("// Player 2 Patterns") != string::npos) {
        return 7;
    } else if (line.find("// Player 1 Mosaic/GameBoard") != string::npos) {
        return 8;
    } else if (line.find("// Player 2 Mosaic/GameBoard") != string::npos) {
        return 9;
    } else {
        return -1;
    }
}