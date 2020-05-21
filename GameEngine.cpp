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

#define NUM_PLAYERS 2
#define NUM_FACTORIES 6
#define NUM_TILES 20

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
    this->firstPlayerToken = new Tile(FIRST_PLAYER);
    this->playerNumTurn = 0;
}

void GameEngine::startGame() {
    this->startGame(0);
}

void GameEngine::startGame(int isloadGame) {
    if (isloadGame == 0) {
        for(int i = 0; i < NUM_TILES; i++){
            this->tileBag->append(new Tile(RED));
            this->tileBag->append(new Tile(YELLOW));
            this->tileBag->append(new Tile(LBLUE));
            this->tileBag->append(new Tile(DBLUE));
            this->tileBag->append(new Tile(BLACK));
        }

        //Player 1 Creation
        std::string player1name;
        cout << "Enter a name for player 1" << endl;
        cout << "> ";
        std::getline(cin, player1name);
        Player* player1 = new Player(player1name, this->boxLid);
        cout << endl;
        //Player 2 Creation
        std::string player2name;
        cout << "Enter a name for player 2" << endl;
        cout << "> ";
        std::getline(cin, player2name);
        Player* player2 = new Player(player2name, this->boxLid);
        cout << endl;

        this->players[0] = player1;
        this->players[1] = player2;
    }

    cout << "Let's Play!" << endl << endl;
    this->quitGameFlag = false;
    int currentPlayer = isloadGame == 0 ? 0 : this->playerNumTurn;
    while(!this->quitGameFlag){
        round(currentPlayer);
        //Determine who is first next round.
        for(int player = 0; player < 2; player++){
            for(int i = 0; i < FLOOR_SIZE; i++){
                if(players[player]->getFloorTile(i)!=nullptr){
                    if(players[player]->getFloorTile(i)->getColour()==FIRST_PLAYER){
                        currentPlayer = player;
                    }
                }
            }
        }
        //Shift tiles from complete rows & clear board.
        for(Player* player:players){
            for(int i = 0; i < 5; i++){
                player->transferTileOntoWall(i);
            }
            player->nextRound();
        }
        //Check for a winner & handle winning.
        bool finishGame=false;
        for(Player* player: players){
            if(player->completeRow()){
                finishGame=true;
                this->quitGameFlag=true;
                cout<<player->getName()<<" has completed a horizontal row."<<endl;
            }
        }
        if(finishGame){
            cout<<"The game is finished!"<<endl<<"Scores:"<<endl;
            for(Player* player:players){
                player->completeGame();
                cout<<player->getName()<<": "<<player->getScore()<<endl;
            }
            if(players[0]->getScore() > players[1]->getScore()){
                cout<<players[0]->getName()<<" is the winner!"<<endl;
            } else if(players[1]->getScore() > players[0]->getScore()){
                cout<<players[1]->getName()<<" is the winner!"<<endl;
            } else{
                cout<<"It's a tie.";
            }
        }
    }
}

void GameEngine::round(int startingPlayer) {
    int currentPlayer = startingPlayer;
    this->playerNumTurn = currentPlayer;
    //Fill factorys from bag.
    this->factories[0]->moveToContainer(this->boxLid);
    resetFirstPlayerToken();
    for(int factory = 1; factory < 6; factory++){
        this->factories[factory]->moveToContainer(this->boxLid);
        for(int tileNo = 0; tileNo < 4; tileNo++){
            Tile* tile = this->tileBag->getRandomTile();
            if(tile==nullptr){
                this->boxLid->moveAllToContainer(this->tileBag);
                tile = this->tileBag->getRandomTile();
            }
            this->factories[factory]->append(tile);
            this->tileBag->remove(tile);
        }
    }
    //Loop over until all empty or game needs to quit.
    this->quitGameFlag = false;
    while(!this->checkFactoriesEmpty()&&!this->quitGameFlag){
        cout << endl << "TURN FOR PLAYER: " << this->players[currentPlayer]->getName() << endl << endl;
        //Print factories.
        cout<<"Factories:"<<endl;
        for(int factoryNo = 0; factoryNo < NUM_FACTORIES; factoryNo++){
            cout << factoryNo << ": " << this->factories[factoryNo]->toString()<<endl;
        }
        //Print player board.
        cout<<"Mosiac: "<<endl;
        for(int rowNo = 0; rowNo < 5; rowNo++){
            cout<< rowNo + 1 << ": ";
            cout<< this->players[currentPlayer]->toString(rowNo) << endl;
        }
        cout<<"Broken tiles: "<<endl;
        cout<<this->players[currentPlayer]->floorToString() << endl;
        cout<<endl;

        //Player command input:
        bool validInput = false;
        while(!validInput){
            std::vector<std::string> playerCommand = getPlayerTurnCommand();
            if(playerCommand.front()=="turn" && playerCommand.size()>=4){
                try{
                    int factoryIndex = std::stoi(playerCommand.at(1));
                    int patternLine = std::stoi(playerCommand.at(3));
                    patternLine = patternLine - 1; // since we are showing index 0 as 1
                    Factory* targetFactory = this->factories[factoryIndex];
                    std::vector<Tile*> tiles = targetFactory->getAll(playerCommand.at(2).front());
                    if(tiles.size()!=0){
                        if(this->players[currentPlayer]->applyTilesToPattern(patternLine, tiles)){
                            validInput=true;
                            for(Tile* tile:tiles){
                                targetFactory->remove(tile);
                            }
                            targetFactory->moveToFactory(this->factories[0]);
                        } else{
                            cout<<"Couldn't place those tiles into that patternline"<<endl;
                        }
                    } else {
                        cout<<"Couldn't find any of those type of tiles."<<endl;
                    }
                } catch(const std::invalid_argument &){
                    cout<<"Error processing turn command."<<endl;
                }
            } else if(playerCommand.front()=="quit" || cin.eof()){
                cout<<"Quitting program..."<<endl;
                //Handle quit.
                validInput=true;
                this->quitGameFlag=true;
            } else if(playerCommand.front()=="save" && playerCommand.size()>=2){
                cout<<"Saving to file: "<<playerCommand.at(1)<<".azul"<<endl;
                this->saveGame(playerCommand.at(1));
                validInput = true;
            } else if(playerCommand.front()=="skip"){
                cout<<"Skipping turn."<<endl;
                validInput=true;
            } else {
                cout<<"Try again"<<endl;
            }
            //Increment current player
            currentPlayer++;
            currentPlayer = currentPlayer % NUM_PLAYERS;
            this->playerNumTurn = currentPlayer;
        }
    }
}

void GameEngine::saveGame(string fileName) {
    std::ofstream saveFile(fileName);

    saveFile << "// game state data" << endl;
    saveFile << this->factories[0]->toString() << "// factory 0 centre table + first player token" << endl;
    saveFile << this->factories[1]->toString() << "// factory 1" << endl;
    saveFile << this->factories[2]->toString() << "// factory 2" << endl;
    saveFile << this->factories[3]->toString() << "// factory 3" << endl;
    saveFile << this->factories[4]->toString() << "// factory 4" << endl;
    saveFile << this->factories[5]->toString() << "// factory 5" << endl;

    saveFile << endl;

    saveFile << this->tileBag->toString() << "// Tile Bag" << endl;
    saveFile << this->boxLid->toString() << "// Box Lid" << endl;

    saveFile << endl;

    saveFile << "// player 1 save data" << endl;
    saveFile << this->players[0]->getName() << endl;
    saveFile << (this->playerNumTurn == 0 ? "true" : "false") << endl;
    saveFile << this->players[0]->getPlayerPoints() << endl;

    saveFile << endl;

    saveFile << "// Player 1 Patterns" << endl;
    for(int rowNo = 0; rowNo < 5; rowNo++){
        saveFile << this->players[0]->patternsToString(rowNo) << endl;
    }

    saveFile << endl;

    saveFile << "// Player 1 Mosaic/GameBoard" << endl;
    for(int rowNo = 0; rowNo < 5; rowNo++){
        saveFile << this->players[0]->mosiacToString(rowNo) << endl;
    }

    saveFile << endl;

    saveFile << "// Broken tiles 1 + first player token" << endl;
    saveFile << this->players[0]->floorToString() << endl;

    saveFile << endl;

    saveFile << "// player 2 save data" << endl;
    saveFile << this->players[1]->getName() << endl;
    saveFile << (this->playerNumTurn == 0 ? "false" : "true") << endl;
    saveFile << this->players[1]->getPlayerPoints() << endl;

    saveFile << endl;

    saveFile << "// Player 2 Patterns" << endl;
    for(int rowNo = 0; rowNo < 5; rowNo++){
        saveFile << this->players[1]->patternsToString(rowNo) << endl;
    }

    saveFile << endl;

    saveFile << "// Player 2 Mosaic/GameBoard" << endl;
    for(int rowNo = 0; rowNo < 5; rowNo++){
        saveFile << this->players[0]->mosiacToString(rowNo) << endl;
    }

    saveFile << endl;

    saveFile << "// Broken tiles 2 + first player token" << endl;
    saveFile << this->players[1]->floorToString() << endl;

    saveFile.close();
}

void GameEngine::loadGame(string filename) {
    std::ifstream saveFile(filename);

    if (saveFile.good()) {
        while (!saveFile.eof()) {
            string line;
            std::getline(saveFile, line);
            int gameType = this->GameType(line);
            if (gameType >= 1 && gameType <= 6) {
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
                for(int rowNo = 0; rowNo < 5; rowNo++){
                    std::getline(saveFile, line);
                    this->loadPlayerPattern(line, rowNo, gameType == 11 ? 0 : 1);
                }
            } else if (gameType == 13 || gameType == 14) {
                for(int rowNo = 0; rowNo < 5; rowNo++){
                    std::getline(saveFile, line);
                    this->loadPlayerMosiac(line, rowNo, gameType == 13 ? 0 : 1);
                }
            } else if (gameType == 15 || gameType == 16) {
                std::getline(saveFile, line);
                this->loadPlayerBrokenTiles(line, gameType == 15 ? 0 : 1);
            }
        }
    }
    this->startGame(1);
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
	unsigned int startPosition = data.find(replace);

	if (startPosition < line.size()) {
		data.replace(startPosition, replace.size(), "");
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
    string replace = "";
    if (pos == 0) {
        replace.append("// factory 0 centre table + first player token");
    } else {
        replace.append("// factory ");
        replace.append(std::to_string(pos));
    }
    splitString = this->split(this->replaceAll(factories, replace), ' ');
    for (string colour : splitString) {
        this->factories[pos]->append(new Tile(colour));
    }
}

void GameEngine::loadPlayerPattern(string pattern, int row, int pos) {
    vector<string> playerPatternString = this->split(pattern, ' ');
    vector<Tile*> tiles;
    for (string colour : playerPatternString) {
        if (colour.compare(".") != 0) {
            tiles.push_back(new Tile(colour));
        }
    }
    this->players[pos]->appendPatterns(row, tiles);
}

void GameEngine::loadPlayerMosiac(string mosiac, int row, int pos) {
    vector<string> playerMosiacString = this->split(mosiac, ' ');
    vector<Tile*> tiles;
    for (string colour : playerMosiacString) {
        if (colour.compare(".") != 0) {
            tiles.push_back(new Tile(colour));
        }
    }
    this->players[pos]->appendMosiac(row, tiles);
}

void GameEngine::loadPlayerBrokenTiles(string brokenTiles, int pos) {
    string replaceString = "// Broken tiles ";
    replaceString.append(std::to_string(pos));
    replaceString.append(" + first player token");
    vector<string> brokenTilesString = this->split(this->replaceAll(brokenTiles, replaceString), ' ');
    vector<Tile*> colourTiles;
    for (string colour : brokenTilesString) {
        if (colour.compare(".") != 0) {
            colourTiles.push_back(new Tile(colour));
        }
    }
    this->players[pos]->appendFloor(colourTiles);
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
    } else if (line.find("// Broken tiles 1 + first player token") != string::npos) {
        return 15;
    } else if (line.find("// Broken tiles 2 + first player token") != string::npos) {
        return 16;
    } else {
        return -1;
    }
}

bool GameEngine::checkGameFinsihed(){
    bool result;
    for(Player* player:this->players){
        if(player->completeRow()){
            result = true;
        }
    }
    return result;
}

bool GameEngine::checkFactoriesEmpty(){
    int tileCount = 0;
    for(int factory = 0; factory < 6; factory++){
        tileCount+=this->factories[factory]->getSize();
    }
    return(tileCount==0);
}

void GameEngine::resetFirstPlayerToken(){
    this->tileBag->remove(this->firstPlayerToken);
    this->boxLid->remove(this->firstPlayerToken);
    this->factories[0]->append(firstPlayerToken);
}

std::vector<std::string> GameEngine::getPlayerTurnCommand(){
    cout<<"> ";
    std::vector<std::string> output;
    std::string input;
    std::getline(cin, input);
    size_t i = 0;
    while ((i = input.find(" ")) != std::string::npos) {
        output.push_back(input.substr(0, i));
        input.erase(0, i+1);
    }
    output.push_back(input);    //Needed to catch the last part of the split input.
    return output;
}