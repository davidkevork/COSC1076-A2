#include "BoxLid.h"

BoxLid::BoxLid(){
    this->tiles = new TileLList();
}

BoxLid::~BoxLid(){
    this->tiles->~TileLList();
}

bool BoxLid::append(Tile* tile){
    this->tiles->append(tile);
    return true;
}

bool BoxLid::remove(Tile* tile){
    bool result = false;
    Tile* removedTile = this->tiles->remove(tile);
    if(removedTile!=nullptr){
        result = true;
    }
    return result;
}

bool BoxLid::contains(Tile* tile){
    bool result = false;
    for(int i = 0; i < this->tiles->size(); i++){
        if(this->tiles->getTile(i)==tile){
            result = true;
        }
    }
    return result;
}

bool BoxLid::contains(Colour colour){
    bool result = false;
    for(int i = 0; i < this->tiles->size(); i++){
        if(this->tiles->getTile(i)->getColour()==colour){
            result=true;
        }
    }
    return result;
}

std::string BoxLid::toString() {
    return this->tiles->toString();
}
void BoxLid::moveAllToContainer(TileContainer* container){
    while(this->tiles->size() > 0){
        Tile* target = this->tiles->getFirst();
        container->append(target);
        this->tiles->remove(target);
    }
}
