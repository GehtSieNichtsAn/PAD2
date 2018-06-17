/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DungeonMap.h
 * Author: stud
 *
 * Created on 25. April 2018, 11:26
 */

#ifndef DUNGEONMAP_H
#define DUNGEONMAP_H
#include <vector>
#include <string>
#include <set>
#include "Tile.h"
#include "Passive.h"
#include "Active.h"
#include "Character.h"

using namespace std;

class DungeonMap
{
public:
    struct Position {
        int Reihe;
	int Spalte;
    };
    
    struct Kanten {
        Position knoten1;
	Position knoten2;
    };
    
    DungeonMap(int height, int width);
    DungeonMap(string spielfeldfile, string parameterfile);
    virtual ~DungeonMap();
    
    void display();
    void place(Position pos, Character* character);
    
    Position find(Tile* t);
    Tile* find(Position pos);
    Position find(Character* character);
   
    int getWidth();
    int getHeight();
    
    vector<Character*>& getCharacters();    
    void getPathTo(Position from, Position to);
    
private:

    Position m_pos;
    int m_height;
    int m_width;
    Tile*** m_field;
    
    vector<Character*> m_spielfiguren;
    
    set<Position> m_positions;
    set<Kanten> m_kanten;
    
    
};

#endif /* DUNGEONMAP_H */

