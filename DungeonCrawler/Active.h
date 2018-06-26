/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Active.h
 * Author: stud
 *
 * Created on 25. Mai 2018, 16:57
 */

#ifndef ACTIVE_H
#define ACTIVE_H
#include <vector>
#include "Tile.h"

class Passive;

class Active : public Tile {    
public:
   
    void attach(Passive* toAttach);
    void detach(Passive* toDetach);
    
protected:
    bool m_activated;
    Active();  
    
    vector<Passive*> PassiveList;
   
};


class Switch : public Active {
public:
    
    Switch(string status);
    void onEnter(Character* character) override;
    bool canEnter() override;


};


class Lever : public Active {
public:
    
    Lever();
    void onEnter(Character* character) override;
    bool canEnter() override;

    
};


class Trap : public Active {
public: 
    
    Trap(); 
    void onEnter(Character* character) override;

};


class Portal : public Active {
public:
    
    Portal();
    void onEnter(Character* character) override;
    void setPortal(Portal* p);
private: 
    
    int m_connectedPortal_Reihe;
    int m_connectedPortal_Spalte;
    Portal* m_portal;
    
};
#endif /* ACTIVE_H */

