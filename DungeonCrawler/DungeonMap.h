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
        Position m_self;
        Position m_source;
        bool m_visited;
        Kanten(Position m_self, Position m_source, bool m_visited);
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
    
    void getKanten(set<Kanten>& Kanten, Position from);
    
    vector<Character*>& getCharacters();    
    set<Position> getPathTo(Position from, Position to);
    
    void clearSets();
    
private:

    Position m_pos;
    int m_height;
    int m_width;
    Tile*** m_field;
    
    vector<Character*> m_spielfiguren;     
    
    set<Kanten> m_kanten;
    set<Position> m_path;
    
};



#endif /* DUNGEONMAP_H */

