/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GameEngine.h
 * Author: stud
 *
 * Created on 26. April 2018, 09:15
 */

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "DungeonMap.h"
#include "Character.h"

class GameEngine
{
public:
    
    GameEngine();
    virtual ~GameEngine();
    
    int turn();
    void run();
    bool finished();
    void saveToFile();
    void loadFromFile();
    
private:

    DungeonMap* m_dng;
    vector<Character*> m_spielfiguren;
    DungeonMap::Position nextPos;
};

#endif /* GAMEENGINE_H */

