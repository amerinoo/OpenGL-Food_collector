/*
 * Project name: Food collection
 * Version 1
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#include "enemy.h"
using namespace std;


    
// Constructors
Enemy::Enemy(){
    points = 0;
}


// Getters 
char Enemy::getSymbol(){return 'e';}

CellType Enemy::getType(){return ENEMY;}

void Enemy::eat(){}

void Enemy::draw(){
	glColor3f(1, 0, 0);

	Agent::draw();
}