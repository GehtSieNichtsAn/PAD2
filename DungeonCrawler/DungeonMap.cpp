/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DungeonMap.cpp
 * Author: stud
 * 
 * Created on 25. April 2018, 11:26
 */
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include "DungeonMap.h"
#include "Controller.h"

using namespace std;

DungeonMap::DungeonMap(int height, int width) : m_height(height), m_width(width) {
    
    m_field = new Tile**[m_height];
    for(int i = 0; i < m_height; ++i) {
        m_field[i] = new Tile*[m_width];
    }
    
    //2D Array mit Nullptr initialisieren
    for(int i = 0; i < m_height; i++) {
        for(int j = 0; j < m_width; j++) {
            m_field[i][j] = NULL;
        }
    }

}

DungeonMap::DungeonMap(string spielfeldfile, string parameterfile) {
           
    //AUS TEXTDATEI
    
    //Spielfeld einlesen START//
   
    int Reihen = 0;
    int Spalten = 0;
    string Daten;    
   
 
    string dateipfad = "/home/stud/Schreibtisch/PAD2/DungeonCrawler_V4/";
    ifstream gamefield;  
    
    //gamefield.open(dateipfad+spielfeldfile);
    gamefield.open("Spielfeld.txt");
    gamefield >> m_height >> m_width;
    
    m_field = new Tile**[m_height];
    for(int i = 0; i < m_height; ++i) {
        m_field[i] = new Tile*[m_width];
    }
    
    for(int i = 0; i < m_height; i++) {
        gamefield >> Daten;
        for(int j = 0; j < m_width; j++) {
            if(Daten[j] == '#') {
                m_field[i][j] = new Wall();
            } else if(Daten[j] == '.') {
                m_field[i][j] = new Floor();
            }  
        }
    }
    
    gamefield.close();
    //Spielfeld einlesen ENDE//
    
    
    Reihen = 0;
    Spalten = 0;
    
   
    ifstream parameter;
    
    //parameter.open(dateipfad+parameterfile);
    parameter.open("Parameter.txt");
    
    for(int i = 0; i < 29; i++) {           
        string status; 
        string ParameterType;
        string controller;
        string muster;
        string onCharacter = "";
        char symbol;
        int ReihenPassive = 0;
        int SpaltenPassive = 0;
        int stamina = 0;
        int strength = 0;        
        Position pos;
            
        
        parameter >> ParameterType;
        
        if(ParameterType == "Switch") {                   
            parameter >> Reihen >> Spalten >> status;                        
            delete m_field[Reihen][Spalten];            
            m_field[Reihen][Spalten] = new Switch(status);            
        } else if(ParameterType == "Door") {    
            parameter >> Reihen >> Spalten >> status;           
            delete m_field[Reihen][Spalten];           
            m_field[Reihen][Spalten] = new Door(status);
        } else if(ParameterType == "Character") {
            
            parameter >> Spalten >> Reihen >> symbol >> strength >> stamina >> controller;
            pos.Spalte = Spalten;
            pos.Reihe = Reihen;          
            Character *character = new Character(symbol, strength, stamina);
            m_spielfiguren.push_back(character);              
            
            if(controller == "ConsoleController") {
                ConsoleController *ctrl = new ConsoleController();
                ctrl->setCharacter(character);
                character->setController(ctrl);
                m_field[pos.Spalte][pos.Reihe]->onEnter(character); //damit Items direkt beim Spawnen aufgehoben werden 
               
            } else if(controller == "StationaryController") {
                StationaryController *ctrl = new StationaryController();
                ctrl->setCharacter(character);
                character->setController(ctrl);
               
            } else if(controller == "GuardController") {                  
                parameter >> muster;
                GuardController *ctrl = new GuardController(muster);
                ctrl->setCharacter(character);
                character->setController(ctrl);
                
            } else if(controller == "AttackController") {                  
                parameter >> muster;
                AttackController *ctrl = new AttackController();
                ctrl->setCharacter(character);
                character->setController(ctrl);
                
            }    
            
           place(pos ,character); 
            
        } else if(ParameterType == "Lever") {
            parameter >> Reihen >> Spalten;           
            delete m_field[Reihen][Spalten];            
            m_field[Reihen][Spalten] = new Lever();
        } else if(ParameterType == "Active") {
            parameter >> Reihen >> Spalten >> ReihenPassive >> SpaltenPassive;         
            static_cast<Active*>(m_field[Reihen][Spalten])->attach(static_cast<Passive*>(m_field[ReihenPassive][SpaltenPassive]));           
        } else if(ParameterType == "Portal") {
            parameter >> Reihen >> Spalten >> ReihenPassive >> SpaltenPassive;           
            delete m_field[Reihen][Spalten];
            delete m_field[ReihenPassive][SpaltenPassive];             
            Portal *p1 = new Portal();
            m_field[Reihen][Spalten] = p1;
            Portal *p2 = new Portal();
            m_field[ReihenPassive][SpaltenPassive] = p2;
            p1->setPortal(p2);
            p2->setPortal(p1);            
        } else if(ParameterType == "Trap") {
            parameter >> Reihen >> Spalten;            
            delete m_field[Reihen][Spalten];            
            m_field[Reihen][Spalten] = new Trap();
        } else if(ParameterType == "Shield") {
            parameter >> Reihen >> Spalten;            
            Shield *shield = new Shield();
            static_cast<Floor*>(m_field[Reihen][Spalten])->placeItem(shield);
        } else if(ParameterType == "Greatsword") {
            parameter >> Reihen >> Spalten;            
            Greatsword *gsword = new Greatsword();
            static_cast<Floor*>(m_field[Reihen][Spalten])->placeItem(gsword);
        } else if(ParameterType == "ArmingSword") {
            parameter >> Reihen >> Spalten;            
            Arming_Sword *asword = new Arming_Sword();
            static_cast<Floor*>(m_field[Reihen][Spalten])->placeItem(asword);
        } else if(ParameterType == "Club") {
            parameter >> Reihen >> Spalten;            
            Club *club = new Club();
            static_cast<Floor*>(m_field[Reihen][Spalten])->placeItem(club);
        } else if(ParameterType == "Rapier&Dagger") {
            parameter >> Reihen >> Spalten;            
            Rapier_and_Dagger *rad = new Rapier_and_Dagger();
            static_cast<Floor*>(m_field[Reihen][Spalten])->placeItem(rad);
        } else if(ParameterType == "Gambeson") {
            parameter >> Reihen >> Spalten;
            Gambeson *gambeson = new Gambeson();
            static_cast<Floor*>(m_field[Reihen][Spalten])->placeItem(gambeson);
        } else if(ParameterType == "Mail_Armour") {
            parameter >> Reihen >> Spalten;            
            Mail_Armour *marmour = new Mail_Armour();
            static_cast<Floor*>(m_field[Reihen][Spalten])->placeItem(marmour);
        } else if(ParameterType == "Full_Plate_Armour") {
            parameter >> Reihen >> Spalten;            
            Full_Plate_Armour *fpa = new Full_Plate_Armour();
            static_cast<Floor*>(m_field[Reihen][Spalten])->placeItem(fpa);
        }
       
              
    }
    
    parameter.close();
    
}


DungeonMap::~DungeonMap() {
    
    for(int i = 0; i < m_height; i++) {
        for(int j = 0; j < m_width; j++) {   
            delete m_field[i][j];   
        }
    }
    
    for(int i = 0; i < m_height; i++) {
        delete[] m_field[i];        
    }    
    
    delete[] m_field;
    
}

void DungeonMap::place(Position pos, Character* character) {
    
    m_field[pos.Spalte][pos.Reihe]->setCharacter(character);
   
}

DungeonMap::Position DungeonMap::find(Tile* t) {
    
    for(int i = 0; i < m_height; i++) {
        for(int j = 0; j < m_width; j++) {   
            if(m_field[i][j] == t) {
                m_pos.Spalte = i;
                m_pos.Reihe = j;
                
                return m_pos;
            }   
        }
    }
    
    throw std::runtime_error("Tile not found!");
}

Tile* DungeonMap::find(Position pos) {

    return m_field[pos.Spalte][pos.Reihe];
    
}

DungeonMap::Position DungeonMap::find(Character* character) {
    
    for(int i = 0; i < m_height; i++) {
        for(int j = 0; j < m_width; j++) {   
            if(m_field[i][j]->hasCharacter() == true && m_field[i][j]->getCharacter() == character) {
                m_pos.Spalte = i;
                m_pos.Reihe = j;
                
                return m_pos;
            }            
        }
    }
    
    throw std::runtime_error("Character not found!");
}

void DungeonMap::display() {
    
    for(int i = 0; i < m_width; i++) {
        cout << endl;
        for(int j = 0; j < m_height; j++) {
            if(m_field[i][j]->hasCharacter() == true) {
                cout << (m_field[i][j]->getCharacter())->getSymbol();
            } else {
                cout << m_field[i][j]->getKachelsymbol();
            }  
            
        }
    }
}

vector<Character*>& DungeonMap::getCharacters() {
    return m_spielfiguren;
}

int DungeonMap::getWidth() {
    return m_width;
}

int DungeonMap::getHeight() {
    return m_height;
}

void DungeonMap::getPathTo(Position from, Position to) {
    //cout << to.Spalte << to.Reihe;
    
    
    
    
    
    for(int i = 0; i < m_height; i++) {
        for(int j = 0; j < m_width; j++) {             
                m_pos.Spalte = i;
                m_pos.Reihe = j; 
                
                if(find(m_pos)->getKachelsymbol() == '.' || find(m_pos)->getKachelsymbol() == '*' || find(m_pos)->getKachelsymbol() == '/') {                   
                    m_positions.insert(m_pos);  
                        
                }
                
                       
        }
    }     
   
    for(Position el : m_positions) {
       cout << el.Spalte << " " << el.Reihe << endl;
        
    }

    
   
    
    
    
    
    
    
    
    
    
}

bool operator<(const DungeonMap::Position& lhs, const DungeonMap::Position& rhs) {

    if(lhs.Spalte < rhs.Spalte) {
        return true;
    } else if(lhs.Spalte == rhs.Spalte) {
        if(lhs.Reihe < rhs.Reihe) {
            return true;
        }
    }
    return false;
    
}