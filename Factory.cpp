#include "Factory.h"
#include <vector>
#include <string>
Factory::Factory(){
    
}

Factory::~Factory(){
    for(Tile* tile:this->tiles){
        delete tile;
    }
    delete &this->tiles;
}

std::vector<Tile*> Factory::getAll(){
    return this->tiles;
}

std::vector<Tile*> Factory::getAll(Colour colour){
    std::vector<Tile*> result;
    for(Tile* tile:this->tiles){
        if(tile->getColour()==colour){
            result.emplace_back(tile);
        }
    }
    return result;
}

void Factory::moveToFactory(Factory* factory){
    while(!this->isEmpty()){
        factory->append(this->tiles[0]);
        this->tiles.erase(this->tiles.begin());
    }
}

void Factory::moveToContainer(TileContainer* container){
    while(!this->isEmpty()){
        container->append(this->tiles[0]);
        this->tiles.erase(this->tiles.begin());
    }
}

int Factory::getSize(){
    return this->tiles.size();
}

bool Factory::isEmpty(){
    return (this->tiles.size()==0);
}

std::string Factory::toString(){
    std::string result = "";
    if(this->isEmpty()){
        result =  "";
    } else {
        result+=this->tiles[0]->getColour();
        for(size_t i = 1; i < this->tiles.size(); i++){
            result = result + ' ' + this->tiles[i]->getColour();
        }
    }
    return result;
}

bool Factory::append(Tile* tile){
    this->tiles.push_back(tile);
    return true;
}

bool Factory::remove(Tile* tile){
    bool result = false;
    for(size_t i = 0; i < this->tiles.size(); i++){
        if(this->tiles[i]==tile){
            this->tiles.erase(this->tiles.begin()+i);
            result = true;
        }
    }
    return result;
}

bool Factory::contains(Tile* tile){
    bool result = false;
    for(Tile* i:this->tiles){
        if(i==tile){
            result = true;
        }
    }
    return result;
}

bool Factory::contains(Colour colour){
    bool result = false;
    for(Tile* i:this->tiles){
        if(i->getColour()==colour){
            result = true;
        }
    }
    return result;
}