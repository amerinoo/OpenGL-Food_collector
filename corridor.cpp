/*
 * Project name: Food collection
 * Version 1
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

void Corridor::draw(int i, int j){
    glBegin(GL_QUADS);
    int padding = 0;
    if(hasFood()){ 
        glColor3f(0, 1, 0);
        padding = 7;
    }else glColor3f(1, 0, 0);

    // left up
    glVertex2i(i * Cell::cellWidth + padding, j * Cell::cellHeigth + padding);
    // right up
    glVertex2i((i + 1) * Cell::cellWidth - padding, j * Cell::cellHeigth + padding);
    // right down
    glVertex2i((i + 1) * Cell::cellWidth - padding, (j + 1) * Cell::cellHeigth - padding);
    // left down
    glVertex2i(i * Cell::cellWidth + padding, (j + 1) * Cell::cellHeigth - padding);

    glEnd();
}
