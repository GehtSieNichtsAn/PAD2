/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Controller.cpp
 * Author: stud
 * 
 * Created on 24. Mai 2018, 14:19
 */

#include "Controller.h"
#include <iostream>

using namespace std;

Controller::Controller() {
    
}

Controller::~Controller() {
}

void Controller::setCharacter(Character* c) {
    m_character = c;
}

string Controller::getControllerName() {
    return m_ControllerName;
}

ConsoleController::ConsoleController() {
    m_ControllerName = "ConsoleController";
}

int ConsoleController::move(char symbol) {
    int direction = 0;
    
    cout << endl << "Direction for Character " << symbol << " : ";
    cin >> direction;
  
    return direction;
}

StationaryController::StationaryController() {
    m_ControllerName = "StationaryController";
}


int StationaryController::move(char symbol) {
    return 5;
}

GuardController::GuardController(string muster) {
    m_muster = muster;
    m_ControllerName = "GuardController";
}


int GuardController::move(char symbol) {
    static int cnt = 0;
    if(cnt == m_muster.length()) {
        cnt = 0;
    } 
    
    int direction = m_muster[cnt] - 48;   
    
    cnt++;
    
    return direction;
}

string GuardController::getMuster() {
    return m_muster;
}


AttackController::AttackController() {
    m_ControllerName = "AttackController";
}

int AttackController::move(char symbol) {
    
    
    
    
    
    return 5;
}


