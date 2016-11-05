/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#include "cell.h"
using namespace std;

CellProperties::CellProperties(const char symbol, const Color color, const int padding)
    : symbol(symbol), color(color), padding(padding){ }

const int Cell::cellHeigth = 20;
const int Cell::cellWidth  = 20;

const CellProperties Cell::wallProperties     = CellProperties('0', Colors::wall, 0);
const CellProperties Cell::corridorProperties = CellProperties('.', Colors::corridor, 0);
const CellProperties Cell::foodProperties     = CellProperties('*', Colors::food, 7);
const CellProperties Cell::playerProperties   = CellProperties('p', Colors::player, 5);
const CellProperties Cell::enemyProperties    = CellProperties('e', Colors::enemy, 5);

// Constructors
Cell::Cell(){ }

Cell::Cell(int x, int y, CellType cellType){
    this->x        = x;
    this->y        = y;
    this->cellType = cellType;
    visited        = false;

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

CellType Cell::getType(){ return cellType; }

char Cell::getSymbol(){
    return getProperties().symbol;
}

// Setters
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

void Cell::eat(){ }


bool Cell::hasFood(){ return false; }

void Cell::draw(){
    Color color = getProperties().color;
    int padding = getProperties().padding;

    glColor3f(color.red, color.green, color.blue);
    glBegin(GL_QUADS);

    glVertex2i(getY() * Cell::cellWidth + padding, getX() * Cell::cellHeigth + padding);
    glVertex2i((getY() + 1) * Cell::cellWidth - padding, getX() * Cell::cellHeigth + padding);
    glVertex2i((getY() + 1) * Cell::cellWidth - padding, (getX() + 1) * Cell::cellHeigth - padding);
    glVertex2i(getY() * Cell::cellWidth + padding, (getX() + 1) * Cell::cellHeigth - padding);

    glEnd();
}

CellProperties Cell::getProperties(){
    switch (getType()) {
        case CELL: break;
        case WALL:
            return Cell::wallProperties;

        case CORRIDOR:
            return Cell::corridorProperties;

        case FOOD:
            return Cell::foodProperties;

        case AGENT: break;
        case PLAYER:
            return Cell::playerProperties;

        case ENEMY:
            return Cell::enemyProperties;
    }
    return Cell::wallProperties;
}
