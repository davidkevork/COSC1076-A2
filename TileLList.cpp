#include <iostream>
#include "TileLList.h"
#include "TileNode.h"

TileLList::TileLList() {
    this->_size = 0;
    this->head = nullptr;
    this->tail = nullptr;
}

TileLList::~TileLList() {}

Tile* TileLList::getTile(int index) {
    if (index < 0 || index > this->size()) {
        throw std::runtime_error("Index out of range");
    } else {
        TileNode* returnTile = this->head;
        for (int i = 1; i < index; i++) {
            returnTile = returnTile->getNext();
        }
        return returnTile->getTile();
    }
}

Tile* TileLList::getFirst() {
    return this->head != nullptr ? this->head->getTile() : nullptr;
}

Tile* TileLList::getLast() {
    return this->tail != nullptr ? this->tail->getTile() : nullptr;
}

bool TileLList::insert(int position, Tile* tile) {
    if (position < 0 || position > this->size()) {
        throw std::runtime_error("Index out of range");
    } else {
        TileNode* previousNode = nullptr;
        TileNode* currentNode = this->head;
        for (int i = 0; i < position; i++) {
            previousNode = currentNode;
            currentNode = currentNode->getNext();
        }
        TileNode* newTile = new TileNode(tile, currentNode);
        if (this->head == currentNode) {
            this->head = newTile;
        }
        if (previousNode != nullptr) {
            previousNode->setNext(newTile);
        }
    }
    return true;
}

void TileLList::append(Tile* tile) {
    TileNode* newTile = new TileNode(tile, nullptr);
    if (this->head == nullptr) {
        this->head = newTile;
        this->tail = newTile;
    } else {
        this->tail->setNext(newTile);
        this->tail = newTile;
    }
}

int TileLList::size() {
    return this->_size;
}

void TileLList::setSize(int size) {
    this->_size = size;
}

Tile* TileLList::remove(int position) {
    if (position < 0 || position > this->size()) {
        throw std::runtime_error("Index out of range");
    } else {
        Tile* returnTile = nullptr;
        TileNode* previousNode = nullptr;
        TileNode* currentNode = this->head;
        for (int i = 0; i < position - 1; i++) {
            previousNode = currentNode;
            currentNode = currentNode->getNext();
        }
        returnTile = currentNode->getTile();
        this->removeTileNode(previousNode, currentNode);
        return returnTile;
    }
}

Tile* TileLList::remove(Tile* tile) {
    Tile* returnTile = nullptr;
    TileNode* previousNode = nullptr;
    TileNode* currentNode = this->head;
    int i = 0;
    while (returnTile == nullptr && i < this->size()) {
        if (currentNode->getTile() == tile) {
            returnTile = currentNode->getTile();
        } else {
            i += 1;
            previousNode = currentNode;
            currentNode = currentNode->getNext();
        }
    }
    if (returnTile != nullptr) {
        this->removeTileNode(previousNode, currentNode);
    }
    return returnTile;
}

void TileLList::removeTileNode(TileNode* previousNode, TileNode* currentNode)
{
    if (previousNode == nullptr && currentNode->getNext() == nullptr) { // only one node
        this->head = nullptr;
        this->tail = nullptr;
    } else if (previousNode == nullptr && currentNode->getNext() != nullptr) { // node at head
        this->head = currentNode->getNext();
    } else if (currentNode->getNext() == nullptr) { // node at tail
        previousNode->setNext(nullptr);
        this->tail = previousNode;
    } else {
        previousNode->setNext(currentNode->getNext());
    }
    delete currentNode;
}
