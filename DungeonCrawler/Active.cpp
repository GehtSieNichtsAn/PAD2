/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Active.cpp
 * Author: stud
 * 
 * Created on 25. Mai 2018, 16:57
 */

#include "Active.h"
#include "Passive.h"
#include "Character.h"

Active::Active() {
}

void Active::attach(Passive* toAttach) {
    PassiveList.push_back(toAttach);
}

void Active::detach(Passive* toDetach) {

    for(int i = 0; i < PassiveList.size(); i++) {
        if(PassiveList[i] == toDetach) {
            PassiveList.erase(PassiveList.begin()+i);
        }
    }
}


Switch::Switch(string status) {
    if(status == "off") {
        m_kachelsymbol = '?';
    } else {
        m_kachelsymbol = '!';
    }
}

void Switch::onEnter(Character* character) {
    this->m_character = character;    
    m_kachelsymbol = '!';
    
    for(Passive* PassiveEl : PassiveList) {
        PassiveEl->notify();
    }
    
}

bool Switch::canEnter() {
    return true;
}



Lever::Lever() {
    m_kachelsymbol = 'L';   
}

void Lever::onEnter(Character* character) {
    this->m_character = character;
    
    for(Passive* PassiveEl : PassiveList) {
        PassiveEl->notify();
    }
    
}


Trap::Trap() {
    m_kachelsymbol = '.';
}

void Trap::onEnter(Character* character) {
    this->m_character = character;
    if(m_kachelsymbol != 'T') {
        character->setHitpoints(20);
    }
    m_kachelsymbol = 'T';       
}

Portal::Portal() {
    m_kachelsymbol = 'O';   
}

void Portal::onEnter(Character* character) {
    this->m_character = NULL;
    m_portal->setCharacter(character);
}

void Portal::setPortal(Portal* p) {
    m_portal = p;
}




