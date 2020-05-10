#include "TileNode.h"

TileNode::TileNode(Tile* tile, TileNode* next): tile(tile), next(next) {}

TileNode::TileNode(TileNode* other): tile(other->getTile()), next(other->getNext()) {}

TileNode::TileNode(TileNode&& other): tile(other.getTile()), next(other.getNext()) {}

TileNode::~TileNode() {
  if (this->tile != nullptr) {
    delete this->tile;
  }
  if (this->next != nullptr) {
    delete this->next;
  }
}

Tile* TileNode::getTile() {
  return this->tile;
}

void TileNode::setTile(Tile* tile) {
  if (tile != nullptr) {
    this->tile = tile;
  }
}

TileNode* TileNode::getNext() {
  return this->next;
}

void TileNode::setNext(TileNode* next) {
  this->next = next;
}
