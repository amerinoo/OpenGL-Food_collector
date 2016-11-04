/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#include "wall.h"

// Constructors
Wall::Wall(int a, int b)
    : Cell(a, b){ }

// Getters
CellType Wall::getType(){
    return WALL;
}

char Wall::getSymbol(){
    return '0';
}

void Wall::draw(){
    glColor3f(Colours::wall.red, Colours::wall.green, Colours::wall.blue);
    Cell::draw();
}
