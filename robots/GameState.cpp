/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 * Updated for TDDD86, 2021.
 */

#include "GameState.h"
#include "utilities.h"
#include "constants.h"
#include <iostream>


GameState::GameState(int numberOfRobots) {
   units.clear();
   for (int i = 0; i < numberOfRobots; i++) {
        units.push_back(new Robot());
        std::cout << units.size() << std::endl;
    }
    teleportHero();
}

GameState::GameState(GameState const &gameState){
    hero = gameState.hero;
    for(Unit* unit: gameState.units){
        units.push_back(unit->clone());
    }
}

void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    hero.draw(scene);
    for (const Unit* unit: units)
        unit->draw(scene);

}

void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(hero));
}

void GameState::moveRobots() {
    for(Unit* unit: units){
        unit->moveTowards(hero.asPoint());
    }
}


void GameState::updateCrashes() {
    for(unsigned i=0; i < units.size(); i++){
        for(unsigned j=i+1; j < units.size(); j++){
            if(units[i]->at(*units[j])){
                units[i]->doCrash();
                units[j]->doCrash();
            }
        }
    }
}

int GameState::countToBeJunked()const{
    int numberDestroyed =0;
    for(unsigned i=0; i < units.size(); ++i)
        if(units[i]->isToBeJunked())
            numberDestroyed++;
    return numberDestroyed;
}

void GameState::junkTheCrashed(){
    for(unsigned i=0; i < units.size(); ++i){
        if (units[i]->isToBeJunked()) {
            delete units[i];
            Junk *junk = new Junk(units[i]->asPoint());
            units.push_back(junk);
            units[i] = units[units.size()-1];
            units.pop_back();
        }
    }
}

bool GameState::someRobotsAlive() const {
    for(unsigned i=0; i < units.size(); ++i)
        if(units[i]->isAlive())
            return true;
    return false;
}


bool GameState::heroDead() const {
    for(const Unit *unit: units){
        if(hero.at(*unit)){
            return true;
        }
    }
    return false;
}


void GameState::moveHeroTowards(const Point& dir) {
    hero.moveTowards(dir);
}

Point GameState::getHeroAsPoint() const {return hero.asPoint();}

/*
 * Free of robots and junk
 */
bool GameState::isEmpty(const Unit& unitCon) const {
    for(const Unit *unit: units){
        if(unit->at(unitCon))
            return false;
    }
    return true;
}

