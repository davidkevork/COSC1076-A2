#include "BoxLid.h"

BoxLid::BoxLid(){
    this->tiles = new TileLList();
}

BoxLid::~BoxLid(){
    this->tiles->~TileLList();
}