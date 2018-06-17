/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Passive.cpp
 * Author: stud
 * 
 * Created on 25. Mai 2018, 16:59
 */

#include "Passive.h"
#include "Active.h"
#include <iostream>

Passive::Passive() {
}

Door::Door(string status) {
        
    if(status == "open") {
        m_activated = true;
        m_kachelsymbol = '/';
    } else {
        m_activated = false;
        m_kachelsymbol = 'X';
    }
}

bool Door::canEnter() {
    if(this->getKachelsymbol() == 'X') {
        return false;
    }
    
    return true;
}

void Door::notify() {
    
    if(m_activated == true) {
        m_kachelsymbol = 'X';
        m_activated = false;
    } else {
        m_kachelsymbol = '/';
        m_activated = true;
    }
}

