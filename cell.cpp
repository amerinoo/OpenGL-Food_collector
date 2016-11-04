/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#include "cell.h"
using namespace std;

const int Cell::cellHeigth = 20;
const int Cell::cellWidth  = 20;

// Constructors
Cell::Cell(){ }

Cell::Cell(int a, int b){
    x       = a;
    y       = b;
    visited = false;

    up    = NULL;
    down  = NULL;
    left  = NULL;
    right = NULL;
}

// Getters
int Cell::getX(){ return x; }

int Cell::getY(){ return y; }

bool Cell::isVisited(){ return visited; }

Cell * Cell::getUp(){ return up; }

Cell * Cell::getDown(){ return down; }

Cell * Cell::getLeft(){ return left; }

Cell * Cell::getRight(){ return right; }

CellType Cell::getType(){ return CELL; }

char Cell::getSymbol(){ return '_'; }

// Setters
void Cell::setVisited(bool b){ visited = b; }

void Cell::setUp(Cell * c){ up = c; }

void Cell::setDown(Cell * c){ down = c; }

void Cell::setLeft(Cell * c){ left = c; }

void Cell::setRight(Cell * c){ right = c; }

// Print
void Cell::print(){ cout << getX() << " " << getY() << endl; }

void Cell::eat(){ }


bool Cell::hasFood(){ return false; }

void Cell::draw(){
    draw(0);
}

void Cell::draw(int padding){
    glBegin(GL_QUADS);

    glVertex2i(getY() * Cell::cellWidth + padding, getX() * Cell::cellHeigth + padding);
    glVertex2i((getY() + 1) * Cell::cellWidth - padding, getX() * Cell::cellHeigth + padding);
    glVertex2i((getY() + 1) * Cell::cellWidth - padding, (getX() + 1) * Cell::cellHeigth - padding);
    glVertex2i(getY() * Cell::cellWidth + padding, (getX() + 1) * Cell::cellHeigth - padding);

    glEnd();
}
