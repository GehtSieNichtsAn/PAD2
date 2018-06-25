/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tile.cpp
 * Author: stud
 * 
 * Created on 24. April 2018, 17:47
 */

#include "Tile.h"
#include "Passive.h"
#include <iostream>

using namespace std;

Tile::Tile() {
    m_character = NULL;
}

Tile::~Tile() {
}

char Tile::getKachelsymbol() const {
    return m_kachelsymbol;
}

Character* Tile::getCharacter() const {
    return m_character;
}

void Tile::setCharacter(Character* character) {
    m_character = character;
}

bool Tile::hasCharacter() {
    
    if(m_character != NULL) {
        return true;
    }
    
    return false;
}

bool Tile::canEnter() {    
    if (m_character == NULL) {
        return true;
    }

    return false;
}

void Tile::onLeave(Tile* toTile) {

    if(toTile->canEnter() == true) {
        toTile->onEnter(this->getCharacter());    
        this->m_character = NULL;        
    }
}

void Tile::onEnter(Character* character) {
    this->m_character = character;
}

vector<Item*> Floor::getItemsOnTile() {
    return m_ItemsOnTile;
}

//////////////Floor Start//////////////

Floor::Floor() {
    m_kachelsymbol = '.';
}

Floor::~Floor() {
    for(Item* item : m_ItemsOnTile) {
        delete item;
    }
}

void Floor::onLeave(Tile* toTile) {

    if(toTile->canEnter() == true && toTile->getCharacter() == NULL) {
        toTile->onEnter(this->getCharacter());    
        this->m_character = NULL;         
    } else if(toTile->getCharacter() != NULL) {        
        toTile->onEnter(this->getCharacter());   
    }
    //fehler wtf kp
    
//    if(toTile->canEnter() == true) {
//        toTile->onEnter(this->getCharacter());    
//        this->m_character = NULL;        
//    }

    
}

bool Floor::canEnter() {   
    return true;
}


void Floor::placeItem(Item* item) {
    m_kachelsymbol = '*';
    m_ItemsOnTile.push_back(item);
}

void Floor::onEnter(Character* character) {
    
    if(this->m_character == NULL) {        
        this->m_character = character;        
    } else {
        //Kampf   
        cout << "Test;";
        this->m_character->setHitpoints(character->getStrength());
        
        if(this->m_character->getHitpoints() < 1) {
            cout << "LOL";
            this->m_character = character;
        } else {
            character->setHitpoints(this->m_character->getStrength());
        }
        
    }
    
    
    //this->m_character = character; 
    if(this->m_ItemsOnTile.empty() == false) {
        character->addItem(m_ItemsOnTile);
        m_ItemsOnTile.clear();
        m_kachelsymbol = '.';
    }  
}
//////////////Floor End////////////////


//////////////Wall Start///////////////

Wall::Wall() {
    m_kachelsymbol = '#';
}

bool Wall::canEnter() {
    return false;
}

//////////////Wall End/////////////////
