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
    if(hasFood()){ 
        int padding = 7;

        glColor3f(0, 1, 1);
        
        glBegin(GL_QUADS);

        glVertex2i(i * Cell::cellWidth + padding, j * Cell::cellHeigth + padding);
        glVertex2i((i + 1) * Cell::cellWidth - padding, j * Cell::cellHeigth + padding);
        glVertex2i((i + 1) * Cell::cellWidth - padding, (j + 1) * Cell::cellHeigth - padding);
        glVertex2i(i * Cell::cellWidth + padding, (j + 1) * Cell::cellHeigth - padding);

        glEnd();
    }


}
