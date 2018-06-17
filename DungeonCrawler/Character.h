/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Character.h
 * Author: stud
 *
 * Created on 25. April 2018, 11:10
 */

#ifndef CHARACTER_H
#define CHARACTER_H
#include "Controller.h"
#include "Item.h"
#include <vector>

class Character
{
public:
    Character(char symbol, int strength, int stamina);
    virtual ~Character();
    
    char getSymbol() const;
    int move();
    
    int getMaxHP();
    int getStrength(Item* item);
    int getStamina(Item* item);
    int getHitpoints();
    void showInfo();
    
    void addItem(vector<Item*> item);
    
    void setHitpoints(int damage);
    
    void setController(Controller* ctrl);
    Controller* getController();
    std::vector<Item*> getCharacterItems();
    
    int getStrength();
    int getStamina();
private:

    const char m_symbol;
    Controller* m_control;
     
    int m_strength;
    int m_stamina;
    int m_hitpoints;
     
    std::vector<Item*> m_CharacterItems;
};

#endif /* CHARACTER_H */

