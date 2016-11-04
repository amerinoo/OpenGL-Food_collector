/*
 * Project name: Food collection
 * Version 1
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

void Wall::draw(int i, int j){
	glBegin(GL_QUADS);
    glColor3f(0, 0, 1);

    glVertex2i(i * Cell::cellWidth, j * Cell::cellHeigth);
    glVertex2i((i + 1) * Cell::cellWidth, j * Cell::cellHeigth);
    glVertex2i((i + 1) * Cell::cellWidth, (j + 1) * Cell::cellHeigth);
    glVertex2i(i * Cell::cellWidth, (j + 1) * Cell::cellHeigth);

    glEnd();
}
