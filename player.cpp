/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#include "player.h"
using namespace std;

// Constructors
Player::Player() : Agent(){ }

Player::Player(Cell * cell) : Agent(cell){
    setCellType(PLAYER);
    goInitPosition();
}
