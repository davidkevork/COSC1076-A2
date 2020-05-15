#include "gameEngine.h"

using std::cin;
using std::cout;
using std::endl;

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
    cout << "=== Start Round "<< this->roundno << " ===" << endl;
    for(Player* player : this->players) {
        cout << "TURN FOR PLAYER: " << player->getName() << endl << endl;
    }
}