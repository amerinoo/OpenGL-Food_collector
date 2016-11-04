/*
 * Project name: Food collection
 * Version 2
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
char Player::getSymbol(){ return 'p'; }

CellType Player::getType(){ return PLAYER; }

void Player::eat(){ }

void Player::draw(){
    glColor3f(Colours::player.red, Colours::player.green, Colours::player.blue);
    Agent::draw();
}
