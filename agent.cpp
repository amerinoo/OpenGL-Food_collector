/*
 * Project name: Food collection
 * Version 1
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#include "agent.h"
using namespace std;


    
// Constructors
Agent::Agent(){
	padding = 5;
}

// Getters 
char Agent::getSymbol(){return 'a';}

CellType Agent::getType(){return AGENT;}

void Agent::eat(){}

void Agent::draw(){}

void Agent::setPosition(Cell* cell){
	position = cell;
}