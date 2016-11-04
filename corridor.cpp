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
    if (hasFood()) {
        glColor3f(Colours::food.red, Colours::food.green, Colours::food.blue);
        Cell::draw(7);
    } else {
        glColor3f(Colours::corridor.red, Colours::corridor.green, Colours::corridor.blue);
        Cell::draw();
    }
}
