/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Item.h
 * Author: stud
 *
 * Created on 1. Juni 2018, 20:05
 */

#ifndef ITEM_H
#define ITEM_H
#include <string>

using namespace std;

class Item {
public:
    Item();
    virtual ~Item();
    
    virtual int modifyStrength(int strength) = 0;
    virtual int modifyStamina(int stamina) = 0;
    string getname();
    
protected:
    string m_ItemName;
};


class Arming_Sword : public Item{
public: 
    Arming_Sword();
    
    int modifyStamina(int stamina) override;
    int modifyStrength(int strength) override;   
};

class Greatsword : public Item{
public: 
    Greatsword();    
    
    int modifyStamina(int stamina) override;
    int modifyStrength(int strength) override;   
};

class Club : public Item{
public: 
    Club();
    
    int modifyStamina(int stamina) override;
    int modifyStrength(int strength) override;   
};

class Rapier_and_Dagger : public Item{
public: 
    Rapier_and_Dagger();
    
    int modifyStamina(int stamina) override;
    int modifyStrength(int strength) override;   
};

class Gambeson : public Item{
public: 
    Gambeson();
    
    int modifyStamina(int stamina) override;  
    int modifyStrength(int strength) override;   
};

class Mail_Armour : public Item{
public: 
    Mail_Armour();
    
    int modifyStamina(int stamina) override;
    int modifyStrength(int strength) override;   
};

class Shield : public Item{
public: 
    Shield();
    
    int modifyStamina(int stamina) override;
    int modifyStrength(int strength) override;   
};

class Full_Plate_Armour : public Item{
public: 
    Full_Plate_Armour();
    
    int modifyStamina(int stamina) override;
    int modifyStrength(int strength) override;   
};


#endif /* ITEM_H */

