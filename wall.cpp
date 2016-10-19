#include "wall.h"

Wall::Wall(int a, int b)
    : Cell(a, b){ }

CellType Wall::getType(){
    return WALL;
}

char Wall::getSymbol(){
    return '0';
}
