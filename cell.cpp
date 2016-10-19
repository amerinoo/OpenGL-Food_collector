#include "cell.h"
using namespace std;

// Constructors
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

Cell ** Cell::getUp(){ return up; }

Cell ** Cell::getDown(){ return down; }

Cell ** Cell::getLeft(){ return left; }

Cell ** Cell::getRight(){ return right; }

CellType Cell::getType(){ return CELL; }

char Cell::getSymbol(){ return '_'; }

// Setters
void Cell::setVisited(bool b){ visited = b; }

void Cell::setUp(Cell ** c){ up = c; }

void Cell::setDown(Cell ** c){ down = c; }

void Cell::setLeft(Cell ** c){ left = c; }

void Cell::setRight(Cell ** c){ right = c; }

// Print
void Cell::printCell(){ cout << getX() << getY() << endl; }
