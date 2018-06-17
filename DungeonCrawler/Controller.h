/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Controller.h
 * Author: stud
 *
 * Created on 24. Mai 2018, 14:19
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <string>

using namespace std;

class Character;

class Controller {
public:
    
    virtual ~Controller();    
    virtual int move(char symbol) = 0;
    void setCharacter(Character* c);
    string getControllerName();
    
protected:
    
    Controller();    
    Character* m_character;
    string m_ControllerName;
};


class ConsoleController : public Controller {
public:
    ConsoleController();
    int move(char symbol) override;
    
};


class StationaryController : public Controller {
public: 
    StationaryController();
    int move(char symbol) override;
    
};


class GuardController : public Controller {
public:
        
    GuardController(string muster);    
    int move(char symbol) override;
    string getMuster();
    
private: 
    string m_muster;
    
};


class AttackController : public Controller {
public: 
    AttackController();
    int move(char symbol) override;
    
};

#endif /* CONTROLLER_H */

