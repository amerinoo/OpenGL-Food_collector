#include "corridor.h"

Corridor::Corridor(int a, int b)
    : Cell(a, b){ }

CellType Corridor::getType(){
    return CORRIDOR;
}

char Corridor::getSymbol(){
    return '.';
}
