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

void GameEngine::saveGame(string fileName) {
    std::ofstream saveFile(fileName);
    saveFile.open(fileName);

    saveFile << "// game state data" << endl;
    saveFile << this->factories[0]->toString() << "// factory 0 centre table + first player token" << endl;
    saveFile << this->factories[1]->toString() << "// factory 1" << endl;
    saveFile << this->factories[2]->toString() << "// factory 2" << endl;
    saveFile << this->factories[3]->toString() << "// factory 3" << endl;
    saveFile << this->factories[4]->toString() << "// factory 4" << endl;
    saveFile << this->factories[5]->toString() << "// factory 5" << endl;

    saveFile << this->tileBag->toString() << "// Tile Bag" << endl;
    saveFile << this->boxLid->toString() << "// Box Lid" << endl;

    saveFile << "// player 1 save data" << endl;
    saveFile << this->players[0]->getName() << endl;
    saveFile << "false" << endl;
    saveFile << this->players[0]->getPlayerPoints() << endl;

    saveFile << "// Player 1 Patterns" << endl;
    // r
    // yy
    // ...
    // bbb.
    // .....

    saveFile << "// Player 1 Mosaic/GameBoard" << endl;
    // . r . y .
    // . r . y .
    // . r . y .
    // . r . y .
    // . r . y .

    saveFile << "// Broken tiles + first player token" << endl;
    // r r b y b y g

    saveFile << "// player 2 save data" << endl;
    saveFile << this->players[1]->getName() << endl;
    saveFile << "true" << endl;
    saveFile << this->players[1]->getPlayerPoints() << endl;

    saveFile << "// Player 2 Patterns" << endl;
    // r
    // yy
    // ...
    // bbb.
    // .....

    saveFile << "// Player 2 Mosaic/GameBoard" << endl;
    // . r . y .
    // . r . y .
    // . r . y .
    // . r . y .
    // . r . y .

    saveFile << "// Broken tiles + first player token" << endl;
    // r r b y b y g
    saveFile.close();
}

void GameEngine::loadGame(string filename) {
    std::ifstream saveFile(filename);

    if (saveFile.good()) {
        while (!saveFile.eof()) {
            string line;
            std::getline(saveFile, line);
            int gameType = this->GameType(line);
            if (gameType >= 1 || gameType <= 6) {
                this->loadFactories(line, gameType - 1);
            } else if (gameType == 7) {
                this->loadTileBag(line);
            } else if (gameType == 8) {
                this->loadBoxLid(line);
            } else if (gameType == 9 || gameType == 10) {
                string name;
                string points;
                std::getline(saveFile, name);
                std::getline(saveFile, line);
                std::getline(saveFile, points);
                this->loadPlayer(name, points, gameType == 9 ? 0 : 1);
            } else if (gameType == 11 || gameType == 12) {
                //
            } else if (gameType == 13 || gameType == 14) {
                //
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

void GameEngine::loadPlayer(string name, string points, int pos) {
    this->players[pos] = new Player(name, this->boxLid);
    this->players[pos]->setPlayerPoints(std::stoi(points));
}

void GameEngine::loadTileBag(string line) {
    vector<string> tileBagString = this->split(this->replaceAll(line, "// Tile Bag"), ' ');
    for (string colour : tileBagString) {
        this->tileBag->append(new Tile(colour));
    }
}

void GameEngine::loadBoxLid(string line) {
    vector<string> boxLidString = this->split(this->replaceAll(line, "// Box Lid"), ' ');
    for (string colour : boxLidString) {
        this->boxLid->append(new Tile(colour));
    }
}


void GameEngine::loadFactories(string factories, int pos) {
    vector<string> splitString;
    if (pos == 0) {
        string factories0;
        factories0.push_back(factories.at(0));
        splitString.push_back(factories0);
    } else {
        string replace = "// factory ";
        replace.push_back(pos);
        splitString = this->split(this->replaceAll(factories, replace), ' ');
    }
    for (string colour : splitString) {
        this->factories[pos]->append(new Tile(colour));
    }
}

int GameEngine::GameType(string line) {
    if (line.find("// factory 0") != string::npos) {
        return 1;
    } else if (line.find("// factory 1") != string::npos) {
        return 2;
    } else if (line.find("// factory 2") != string::npos) {
        return 3;
    } else if (line.find("// factory 3") != string::npos) {
        return 4;
    } else if (line.find("// factory 4") != string::npos) {
        return 5;
    } else if (line.find("// factory 5") != string::npos) {
        return 6;
    } else if (line.find("// Tile Bag") != string::npos) {
        return 7;
    } else if (line.find("// Box Lid") != string::npos) {
        return 8;
    } else if (line.find("// player 1 save data") != string::npos) {
        return 9;
    } else if (line.find("// player 2 save data") != string::npos) {
        return 10;
    } else if (line.find("// Player 1 Patterns") != string::npos) {
        return 11;
    } else if (line.find("// Player 2 Patterns") != string::npos) {
        return 12;
    } else if (line.find("// Player 1 Mosaic/GameBoard") != string::npos) {
        return 13;
    } else if (line.find("// Player 2 Mosaic/GameBoard") != string::npos) {
        return 14;
    } else {
        return -1;
    }
}