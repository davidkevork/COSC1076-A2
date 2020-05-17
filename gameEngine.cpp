#include "gameEngine.h"
#include "Colours.h"

using std::cin;
using std::cout;
using std::endl;

#define NUM_PLAYERS 2
#define NUM_FACTORIES 6

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
    for(int i = 0; i < 10; i++){
        this->tileBag->append(new Tile('R'));
    }
    for(int i = 0; i < 10; i++){
        this->tileBag->append(new Tile('T'));
    }
    for(int i = 0; i < 10; i++){
        this->tileBag->append(new Tile('Y'));
    }
    for(int i = 0; i < 10; i++){
        this->tileBag->append(new Tile('U'));
    }
    for(int i = 0; i < 10; i++){
        this->tileBag->append(new Tile('I'));
    }
}

void gameEngine::startGame() {
    //Player 1 Creation
    std::string player1name;
    cout << "Enter a name for player 1" << endl;
    cout << "> ";
    cin >> player1name;
    Player* player1 = new Player(player1name, this->boxLid);
    cout << endl;
    //Player 2 Creation
    std::string player2name;
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

void gameEngine::startGame(std::string saveGame) {

}

void gameEngine::round() {
    int currentPlayer = 0;
    //Fill factorys from bag.
    for(int factory = 1; factory < 6; factory++){
        for(int tileNo = 0; tileNo < 5; tileNo++){
            Tile* tile = this->tileBag->getRandomTile();
            this->factories[factory]->append(tile);
            this->tileBag->remove(tile);
        }
    }
    //Loop over until all empty.
    while(!this->checkFactoriesEmpty()){
        currentPlayer++;
        currentPlayer = currentPlayer % NUM_PLAYERS;
        cout << "TURN FOR PLAYER: " << this->players[currentPlayer]->getName() << endl << endl;
        //Print factories.
        cout<<"Factories:"<<endl;
        for(int factoryNo = 0; factoryNo < NUM_FACTORIES; factoryNo++){
            cout << factoryNo << ": " << this->factories[factoryNo]->toString()<<endl;
        }
        //Print player board.
    }
    //Players place tiles on wall.

    cout << "=== Start Round "<< this->roundno << " ===" << endl;
    for(Player* player : this->players) {
        cout << "TURN FOR PLAYER: " << player->getName() << endl << endl;
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