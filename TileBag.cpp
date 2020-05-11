#include "TileBag.h"

TileBag::TileBag(){

}

TileBag::~TileBag(){
    for(Tile* tile:this->tiles){
        delete tile;
    }
    delete &this->tiles;
}

std::vector<Tile*> TileBag::getAll(){
    return this->tiles;
}

bool TileBag::append(Tile* tile){
    this->tiles.emplace_back(tile);
    return true;
}

bool TileBag::remove(Tile* tile){
    bool result = false;
    for(size_t i = 0; i < this->tiles.size();i++){
        if(this->tiles[i]==tile){
            this->tiles.erase(this->tiles.begin()+i);
            result = true;
        }
    }
    return result;
}

bool TileBag::contains(Tile* tile){
    bool result = false;
    for(size_t i = 0; i < this->tiles.size(); i++){
        if(this->tiles[i] == tile){
            result = true;
        }
    }
    return result;
}

bool TileBag::contains(Colour colour){
    bool result = false;
    for(size_t i = 0; i < this->tiles.size(); i++){
        if(this->tiles[i]->getColour()==colour){
            result = true;
        }
    }
    return result;
}