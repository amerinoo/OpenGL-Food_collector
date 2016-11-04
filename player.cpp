/*
 * Project name: Food collection
 * Version 1
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#include "player.h"
using namespace std;


    
// Constructors
Player::Player(){
    points = 0;
}


// Getters 
char Player::getSymbol(){return 'p';}

CellType Player::getType(){return PLAYER;}

void Player::eat(){}

void Player::draw(){
	glColor3f(1, 1, 0);

	Agent::draw();

    
}