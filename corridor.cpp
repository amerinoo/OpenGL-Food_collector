/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#include "corridor.h"

// Constructors
Corridor::Corridor(int a, int b) : Cell(a, b){
    food = true;
}

// Getters
CellType Corridor::getType(){ return CORRIDOR; }

char Corridor::getSymbol(){
    if (food) return '*';
    else return '.';
}

bool Corridor::hasFood(){
    return food;
}

void Corridor::eat(){
    this->food = false;
}

void Corridor::draw(){
    int padding;

    if (hasFood()) {
        padding = 7;
        glColor3f(0, 1, 1);
    } else  {
        padding = 0;
        glColor3f(1, 1, 1);
    }

    Cell::draw(padding);
}
