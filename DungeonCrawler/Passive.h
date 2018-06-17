/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Passive.h
 * Author: stud
 *
 * Created on 25. Mai 2018, 16:59
 */

#ifndef PASSIVE_H
#define PASSIVE_H
#include "Tile.h"

class Passive : public Tile {
public:
    
    virtual void notify() = 0;
   
protected:
    bool m_activated;   
    Passive();
};


class Door : public Passive {
public:
    
    Door(string status);
    bool canEnter() override;
    void notify() override;

};

#endif /* PASSIVE_H */

