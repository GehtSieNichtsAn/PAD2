/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tile.h
 * Author: stud
 *
 * Created on 24. April 2018, 17:47
 */


#ifndef TILE_H
#define TILE_H
#include <string>
#include <vector>
#include "Character.h"
#include "Item.h"

using namespace std;

class Tile {
public:
 
    virtual ~Tile();
    
    char getKachelsymbol() const;
    Character* getCharacter() const;
    
    void setCharacter(Character* character);
    
    bool hasCharacter();
    
    virtual bool canEnter();
    virtual void onLeave(Tile* toTile);
    virtual void onEnter(Character* character);
    
protected: 
    Tile();
    
    Character* m_character;
    char m_kachelsymbol;
};


class Floor : public Tile {
public:
    
    Floor(); 
    ~Floor();
    void placeItem(Item *item);
    void onEnter(Character* character) override;
    vector<Item*> getItemsOnTile();
    
private:
    vector<Item*> m_ItemsOnTile;
};


class Wall : public Tile {
public:
    
    Wall();
    
    bool canEnter() override;
};

#endif /* TILE_H */

