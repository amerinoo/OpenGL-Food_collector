/*
 * Project name: Food collection
 * Version 1
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#include "wall.h"

// Constructors
Wall::Wall(int a, int b):
    Cell(a, b){ }

// Getters
CellType Wall::getType(){
    return WALL;
}

char Wall::getSymbol(){
    return '0';
}

void Wall::draw(){
    glColor3f(0, 0, 1);
    Cell::draw();
}
