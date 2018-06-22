/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GameEngine.cpp
 * Author: stud
 * 
 * Created on 26. April 2018, 09:15
 */

#include "GameEngine.h"
#include "DungeonMap.h"
#include "Character.h"
#include "Tile.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "string"
#include "Passive.h"


using namespace std;


GameEngine::GameEngine() {
    
    m_dng = new DungeonMap("Spielfeld.txt", "Parameter.txt");
        
    m_spielfiguren = m_dng->getCharacters();
 
}


GameEngine::~GameEngine() {
    
    delete m_dng;
    
    for(auto c : m_spielfiguren) {
        delete c;
    }
   
}

int GameEngine::turn() {

    int direction = 0;
    
    DungeonMap::Position fromPos;    
    DungeonMap::Position toPos;
    vector<set<DungeonMap::Position>> AllPaths;
    set<DungeonMap::Position> MinimalPath;
    int cnt = 0;
    
    for(Character* spieler : m_spielfiguren) {
        
        //prüfen ob Spieler tot ist
        if(spieler->getHitpoints() < 1) {
            m_spielfiguren.erase(m_spielfiguren.begin() + cnt);
            
            delete spieler;
        }
        cnt++;
        
        
        
        direction = spieler->move();
        
        if(spieler->getController()->getControllerName() == "AttackController") {
            fromPos = m_dng->find(spieler);    
            Tile *fromTile = m_dng->find(fromPos);
            
            //für jeden Gegner kürzesten Weg berechnen
            for(Character* enemy : m_spielfiguren) {
                if(enemy->getController()->getControllerName() == "ConsoleController") {
                    toPos = m_dng->find(enemy);
                    AllPaths.push_back(m_dng->getPathTo(fromPos, toPos));
                    m_dng->clearSets();
                }                 
            }        
            
            
            //kleinste Distanz suchen
            int min = AllPaths[0].size();
            int iterator = 0;
            
            for(int i = 0; i < AllPaths.size(); i++) {
                if(AllPaths[i].size() < min) {
                    min = AllPaths[i].size();
                    iterator = i;
                }
            }     
            
            MinimalPath = AllPaths[iterator];
            
            //vorletzte Position ist nächste Position
            set<DungeonMap::Position>::iterator iter = MinimalPath.begin();
            advance(iter, MinimalPath.size()-2);
            
            nextPos = *iter;
            cout << nextPos.Spalte << " " << nextPos.Reihe;
             
            toPos.Spalte = fromPos.Spalte - (fromPos.Spalte - nextPos.Spalte);
            toPos.Reihe = fromPos.Reihe - (fromPos.Reihe - nextPos.Reihe);
            
            
            Tile *toTile = m_dng->find(toPos);
            fromTile->onLeave(toTile);
            
        } else {
        
            if(direction != 5 && direction <= 9) {

                fromPos = m_dng->find(spieler);
                Tile *fromTile = m_dng->find(fromPos);

                switch(direction) {
                    case 0:
                        //Menü
                        cout << "1. Spiel beenden" << endl;
                        cout << "2. Spielerinfos anzeigen" << endl;
                        cout << "3. Spielstand speichern" << endl;
                        cout << "4. Spielstand laden" << endl;



                        int auswahl;

                        cout << "Auswahl: ";
                        cin >> auswahl;
                        if(auswahl == 1) {
                            exit(0);
                        } else if(auswahl == 2) {                        
                            spieler->showInfo();   
                        } else if(auswahl == 3) {
                            saveToFile();
                        } else if(auswahl == 4) {
                            loadFromFile();
                            return 0;
                        }
                        toPos.Spalte = fromPos.Spalte;
                        toPos.Reihe = fromPos.Reihe; 

                    break;
                    case 1: 
                        toPos.Spalte = fromPos.Spalte + 1;
                        toPos.Reihe = fromPos.Reihe - 1;              
                    break;
                    case 2:
                        toPos.Spalte = fromPos.Spalte + 1;
                        toPos.Reihe = fromPos.Reihe;
                    break;
                    case 3:
                        toPos.Spalte = fromPos.Spalte + 1;
                        toPos.Reihe = fromPos.Reihe + 1;
                    break;
                    case 4:
                        toPos.Spalte = fromPos.Spalte;
                        toPos.Reihe = fromPos.Reihe - 1;
                    break;
                    case 6:
                        toPos.Spalte = fromPos.Spalte;
                        toPos.Reihe = fromPos.Reihe + 1;
                    break;
                    case 7:
                        toPos.Spalte = fromPos.Spalte - 1;
                        toPos.Reihe = fromPos.Reihe - 1;
                    break;
                    case 8:
                        toPos.Spalte = fromPos.Spalte - 1;
                        toPos.Reihe = fromPos.Reihe;
                    break;
                    case 9:
                        toPos.Spalte = fromPos.Spalte - 1;
                        toPos.Reihe = fromPos.Reihe + 1;
                    break;
                    default:

                    break;

                }
                
                Tile *toTile = m_dng->find(toPos);
                fromTile->onLeave(toTile);
                
            }           
        }
    }
    
    
    
    
    return 0;
}

bool GameEngine::finished() {
    DungeonMap::Position CharPos;
    
    for(Character* spieler : m_spielfiguren) {
        
//        if(spieler->getHitpoints() == 0) {
//            return true;
//        }
        
        CharPos = m_dng->find(spieler);
        
        if(CharPos.Spalte == 18 && CharPos.Reihe == 2) {
                return true;
        }
    }
     
    return false; 
   
}



void GameEngine::run() {
    
    m_dng->display();
    
    while(!finished()) {   
        turn();
        
        /*#ifdef __cplusplus__
            #include <cstdlib>
        #else
            #include <stdlib.h>
        #endif

        if (system("CLS")) system("clear");*/
        
        m_dng->display(); 
        
        
    }
}

void GameEngine::saveToFile() {
    
    string spielfeld;
    string parameter;
    
    cout << "Spielfeld, Parameter: ";
    cin >> spielfeld >> parameter;
    
    string dateipfad = "/home/stud/Schreibtisch/PAD2/DungeonCrawler_V3/";
    
    //Spielfeld speichern
    ofstream SpielfeldSave;
    
    SpielfeldSave.open(dateipfad+spielfeld);  
    
    int height = m_dng->getHeight();
    int width = m_dng->getWidth();
    
    SpielfeldSave << height << "\n";
    SpielfeldSave << width;
    
    char Kachelsymbol;
    
    DungeonMap::Position pos;
    for(int i = 0; i < height; i++) {
        SpielfeldSave << "\n";
        for(int j = 0; j < width; j++) {
            pos.Spalte = i;
            pos.Reihe = j;
            
            Kachelsymbol = m_dng->find(pos)->getKachelsymbol();;
            if(Kachelsymbol == '#' || Kachelsymbol == '.') {
                SpielfeldSave << Kachelsymbol;
            } else {
                SpielfeldSave << '.';
            } 
        }
    }    
    
    SpielfeldSave.close();
    
    
    //Parameter speichern
    ofstream ParameterSave;
    ParameterSave.open(dateipfad+parameter);  
    
    vector<DungeonMap::Position> Portale;
    
    for(int i = 0; i < height; i++) {        
        for(int j = 0; j < width; j++) {
            pos.Spalte = i;
            pos.Reihe = j;
            
            Kachelsymbol = m_dng->find(pos)->getKachelsymbol();;
            if(Kachelsymbol == 'X') {
                ParameterSave << "Door " << pos.Spalte << " " << pos.Reihe << " closed \n";
            } else if(Kachelsymbol == '/') {
                ParameterSave << "Door " << pos.Spalte << " " << pos.Reihe << " open \n";
            } else if(Kachelsymbol == 'L') {
                ParameterSave << "Lever " << pos.Spalte << " " << pos.Reihe << "\n"; 
            } else if(Kachelsymbol == '?') {
                ParameterSave << "Switch " << pos.Spalte << " " << pos.Reihe << " off \n";
            } else if(Kachelsymbol == '!') {
                ParameterSave << "Switch " << pos.Spalte << " " << pos.Reihe << " on \n";
            } else if(Kachelsymbol == 'T') { 
                ParameterSave << "Trap " << pos.Spalte << " " << pos.Reihe << "\n";
            } else if(typeid(*(m_dng->find(pos))).name() == typeid(Trap).name()) { 
                ParameterSave << "Trap " << pos.Spalte << " " << pos.Reihe << "\n";
            } else if(Kachelsymbol == 'O') {
                Portale.push_back(pos); //nur möglich wenn es 2 Portale gibt 
            } else if(Kachelsymbol == '*') {
                vector<Item*> ItemsOnTile = static_cast<Floor*>(m_dng->find(pos))->getItemsOnTile();
                for(Item* item : ItemsOnTile) {                    
                    ParameterSave << item->getname() << " " << pos.Spalte << " " << pos.Reihe << "\n";
                }
            }  
           
        }
    }    
  
    
    //Charaktere speichern
    string ControllerName;

    for(Character* spieler : m_spielfiguren) {
        
        pos = m_dng->find(spieler);
        
        vector<Item*> CharacterItems = spieler->getCharacterItems();
        for(Item* item : CharacterItems) {
            ParameterSave << item->getname() << " " << pos.Spalte << " " << pos.Reihe << "\n";
        }
        
        ParameterSave << "Character " << pos.Spalte << " " << pos.Reihe << " " << spieler->getSymbol() << " " << spieler->getStrength() << " " << spieler->getStamina() << " ";
        ControllerName = spieler->getController()->getControllerName();
        
        ParameterSave << ControllerName << " ";
        
        if(ControllerName == "GuardController") {
            ParameterSave << static_cast<GuardController*>(spieler->getController())->getMuster();
        } 
        
        ParameterSave << "\n";
        
        
    }
    
    //Verknüpfungen speichern
    ifstream Parameter;
    Parameter.open("/home/stud/Schreibtisch/PAD2/DungeonCrawler_V3/Parameter.txt");  
    string Daten;
    while(!Parameter.eof()) {
    
        getline(Parameter, Daten);
        int FinderPos = Daten.find(" ", 0);    
        string result = Daten.substr(0, FinderPos);
    
        if(result == "Active") {
            ParameterSave << Daten << "\n";
        }
       
    }    
    Parameter.close();
    
    
    //Portale speichern
    ParameterSave << "Portal ";
    
    for(auto portal : Portale) {
        ParameterSave << portal.Spalte << " " << portal.Reihe << " ";
    }   
    
    ParameterSave.close();
    
    
}

void GameEngine::loadFromFile() {
    string spielfeld;
    string parameter;
    
    cout << "Spielfeld, Parameter: ";
    cin >> spielfeld >> parameter;

    delete m_dng;
    for(Character* c : m_spielfiguren) {
        delete c;
    }
    
    m_spielfiguren.clear();
    
    m_dng = new DungeonMap(spielfeld, parameter);
        
    m_spielfiguren = m_dng->getCharacters();  
    
}



