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
