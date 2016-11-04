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

	glBegin(GL_QUADS);
	
    glVertex2i(position->getX() * Cell::cellWidth + padding, position->getY() * Cell::cellHeigth + padding);
    glVertex2i((position->getX() + 1) * Cell::cellWidth - padding, position->getY() * Cell::cellHeigth + padding);
    glVertex2i((position->getX() + 1) * Cell::cellWidth - padding, (position->getY() + 1) * Cell::cellHeigth - padding);
    glVertex2i(position->getX() * Cell::cellWidth + padding, (position->getY() + 1) * Cell::cellHeigth - padding);

    glEnd();
}