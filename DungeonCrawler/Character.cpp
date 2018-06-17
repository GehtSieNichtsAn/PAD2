/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Character.cpp
 * Author: stud
 * 
 * Created on 25. April 2018, 11:10
 */
#include <iostream>
#include "Character.h"
#include "Controller.h"
#include "Tile.h"

using namespace std;

Character::Character(char symbol, int strength, int stamina) : m_symbol(symbol), m_strength(strength), m_stamina(stamina) {  
    m_hitpoints = this->getMaxHP();
}

Character::~Character() {
    delete m_control;
    
    for(Item* item : m_CharacterItems) {
        delete item;
    }
}

char Character::getSymbol() const {
    return m_symbol;
}

int Character::move() {    
    return m_control->move(m_symbol);    
}

int Character::getMaxHP() {
    return 20 + (m_stamina * 5);
}

int Character::getStamina(Item* item) {
    
    m_stamina = item->modifyStamina(m_stamina);
       
    return m_stamina;
}

int Character::getStrength(Item* item) {
    
    m_strength = item->modifyStrength(m_strength);
    
    return m_strength;
}



void Character::showInfo() {
    cout << "Leben: " << this->m_hitpoints << endl; 
    cout << "Ausdauer: " << this->m_stamina << endl;
    cout << "Stärke: " << this->m_strength << endl;
    for(Item* item : m_CharacterItems) {
        cout << item->getname() << endl;
    }
}

void Character::addItem(vector<Item*> item) {
    for(Item* i : item) {
        m_CharacterItems.push_back(i);
        this->getStrength(i);
        this->getStamina(i);
    }
    
    m_hitpoints = m_hitpoints + (this->getMaxHP() - m_hitpoints);
}

void Character::setHitpoints(int damage) {
    m_hitpoints -= damage;
}

void Character::setController(Controller* ctrl) {
    m_control = ctrl;
}

int Character::getHitpoints() {
    return m_hitpoints;
}

Controller* Character::getController() {
    return m_control;
}

std::vector<Item*> Character::getCharacterItems() {
    return m_CharacterItems;
}

int Character::getStrength()
{
    return m_strength;
}

int Character::getStamina()
{
    return m_stamina;
}

