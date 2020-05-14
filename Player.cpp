#include "Player.h"

Player::Player(std::string name, BoxLid* boxLid) {
    this->name = name;
    this->boxLid = boxLid;
}

std::string Player::getName() {
    return this->name;
}