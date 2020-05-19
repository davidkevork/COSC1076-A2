#include "gameEngine.h"
#include "Colours.h"
#include "BoardDefinitions.h"

using std::cin;
using std::cout;
using std::endl;

#define NUM_PLAYERS 2
#define NUM_FACTORIES 6
#define NUM_TILES 20

gameEngine::gameEngine() {
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

    for(int i = 0; i < NUM_TILES; i++){
        this->tileBag->append(new Tile(RED));
        this->tileBag->append(new Tile(YELLOW));
        this->tileBag->append(new Tile(LBLUE));
        this->tileBag->append(new Tile(DBLUE));
        this->tileBag->append(new Tile(BLACK));
    }

    this->firstPlayerToken = new Tile(FIRST_PLAYER);
}

void gameEngine::startGame() {
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

    cout << "Let's Play!" << endl << endl;
    this->quitGameFlag = false;
    int currentPlayer = 0;
    while(!this->quitGameFlag){
        round(currentPlayer);
        //Determine who is first next roung.
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

void gameEngine::startGame(std::string saveGame) {

}

void gameEngine::round(int startingPlayer) {
    int currentPlayer = startingPlayer;
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
        cout << "TURN FOR PLAYER: " << this->players[currentPlayer]->getName() << endl << endl;
        //Print factories.
        cout<<"Factories:"<<endl;
        for(int factoryNo = 0; factoryNo < NUM_FACTORIES; factoryNo++){
            cout << factoryNo << ": " << this->factories[factoryNo]->toString()<<endl;
        }
        //Print player board.
        cout<<"Moziac: "<<endl;
        for(int rowNo = 0; rowNo < 5; rowNo++){
            cout<< rowNo << ": ";
            cout<< this->players[currentPlayer]->toString(rowNo) << endl;
        }
        cout<<"Broken tiles: "<<endl;
        cout<<this->players[currentPlayer]->floorToString() << endl;

        //Player command input:
        bool validInput = false;
        while(!validInput){
            std::vector<std::string> playerCommand = getPlayerTurnCommand();
            if(playerCommand.front()=="turn" && playerCommand.size()>=4){
                try{
                    int factoryIndex = std::stoi(playerCommand.at(1));
                    int patternLine = std::stoi(playerCommand.at(3));
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
                //Handle save.
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
        }
    }
}

bool gameEngine::checkGameFinsihed(){
    bool result;
    for(Player* player:this->players){
        if(player->completeRow()){
            result = true;
        }
    }
    return result;
}

bool gameEngine::checkFactoriesEmpty(){
    int tileCount = 0;
    for(int factory = 0; factory < 6; factory++){
        tileCount+=this->factories[factory]->getSize();
    }
    return(tileCount==0);
}

void gameEngine::resetFirstPlayerToken(){
    this->tileBag->remove(this->firstPlayerToken);
    this->boxLid->remove(this->firstPlayerToken);
    this->factories[0]->append(firstPlayerToken);
}

std::vector<std::string> gameEngine::getPlayerTurnCommand(){
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