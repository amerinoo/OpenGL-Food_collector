/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#include "agent.h"
using namespace std;

// Constructors
Agent::Agent(){ points = -1; }

int Agent::getPoints(){ return points; }

void Agent::setPosition(Cell * cell){
    position = cell;
    if (position->getType() == FOOD)
        eat();
}

void Agent::eat(){
    position->eat();
    points += 1;
}
