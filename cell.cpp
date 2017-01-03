/*
 * Project name: Food collection
 * Version 4
 * Student : Albert Eduard Merino Pulido
 */
#include "cell.h"
using namespace std;

// Constructors
Cell::Cell(){ }

Cell::Cell(float x, float y, CellType cellType){
    this->x        = x;
    this->y        = y;
    this->cellType = cellType;
    visited        = false;

    up    = NULL;
    down  = NULL;
    left  = NULL;
    right = NULL;
}

bool Cell::operator == (Cell * c){
    return getX() == c->getX() && getY() == c->getY();
}

// Getters
float Cell::getX(){ return x; }

float Cell::getY(){ return y; }

float Cell::getKey(){ return getX() * 100 + getY(); }

bool Cell::isVisited(){ return visited; }

Cell * Cell::getUp(){ return up; }

Cell * Cell::getDown(){ return down; }

Cell * Cell::getLeft(){ return left; }

Cell * Cell::getRight(){ return right; }

CellType Cell::getType(){ return cellType; }

char Cell::getSymbol(){
    Drawer& drawer = Drawer::getInstance();

    return drawer.getProperties(cellType).symbol;
}

// Setters
void Cell::setX(float x){ this->x = x; }

void Cell::setY(float y){ this->y = y; }

void Cell::setVisited(bool b){ visited = b; }

void Cell::setUp(Cell * c){ up = c; }

void Cell::setDown(Cell * c){ down = c; }

void Cell::setLeft(Cell * c){ left = c; }

void Cell::setRight(Cell * c){ right = c; }

void Cell::setCellType(CellType cellType){
    this->cellType = cellType;
}

// Print
void Cell::print(){ cout << getX() << " " << getY() << endl; }

bool Cell::hasFood(){ return cellType == FOOD; }

bool Cell::isWall(){ return cellType == WALL; }

bool Cell::isCorridor(){ return cellType == CORRIDOR; }

void Cell::draw(){
    Drawer& drawer = Drawer::getInstance();

    drawer.draw(getType(), getX(), getY(), false);
}
