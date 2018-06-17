/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Item.cpp
 * Author: stud
 * 
 * Created on 1. Juni 2018, 20:05
 */

#include "Item.h"
#include <iostream>

Item::Item() {
}

Item::~Item() {
    
}

int Item::modifyStrength(int strength) {
    return 0;
}

int Item::modifyStamina(int stamina) {
    return 0;
}

string Item::getname() {
    return m_ItemName;
}


//Actual Items

Arming_Sword::Arming_Sword() {
    m_ItemName = "Arming Sword";
}

int Arming_Sword::modifyStamina(int stamina) {
    return stamina;
}

int Arming_Sword::modifyStrength(int strength) {
    return strength + 3;
}

Greatsword::Greatsword() {
    m_ItemName = "Greatsword";
}

int Greatsword::modifyStamina(int stamina) {
    return stamina - 1;
}

int Greatsword::modifyStrength(int strength) {
    return strength + 5;
}

Club::Club() {
    m_ItemName = "Club";
}

int Club::modifyStamina(int stamina) {
    return stamina;
}

int Club::modifyStrength(int strength) {
    return strength + (strength / 2);
}

Rapier_and_Dagger::Rapier_and_Dagger() {
    m_ItemName = "Rapier and Dagger";
}

int Rapier_and_Dagger::modifyStamina(int stamina) {
    return stamina + 1;
}

int Rapier_and_Dagger::modifyStrength(int strength) {
    return strength + 2;
}

Gambeson::Gambeson() {
    m_ItemName = "Gambeson";
}

int Gambeson::modifyStamina(int stamina) {
    return stamina + 1;
}

int Gambeson::modifyStrength(int strength) {
    return strength;
}

Mail_Armour::Mail_Armour() {
    m_ItemName = "Mail Armour";
}

int Mail_Armour::modifyStamina(int stamina) {
    return stamina + 3;
}

int Mail_Armour::modifyStrength(int strength) {
    return strength;
}

Shield::Shield() {
    m_ItemName = "Shield";
}

int Shield::modifyStamina(int stamina) {
    return stamina + stamina;
}

int Shield::modifyStrength(int strength) {
    return strength - 1;
}

Full_Plate_Armour::Full_Plate_Armour() {
    m_ItemName = "Full Plate Armour";
}

int Full_Plate_Armour::modifyStamina(int stamina) {
    return stamina + 6;
}

int Full_Plate_Armour::modifyStrength(int strength) {
    return strength - 2;
}






