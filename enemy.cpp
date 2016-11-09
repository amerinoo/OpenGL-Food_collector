/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#include "enemy.h"
using namespace std;

// Constructors
Enemy::Enemy() : Agent(){ }

Enemy::Enemy(Cell * cell) : Agent(cell){
    setCellType(ENEMY);
    goInitPosition();
}
