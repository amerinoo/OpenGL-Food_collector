/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#include "cell.h"
using namespace std;

CellProperties::CellProperties(const char symbol, const Color color,
  const int padding, const ShapeType shape, const int radius)
    : symbol(symbol), color(color), padding(padding), shape(shape), radius(radius){ }

const int Cell::cellSize = 40;

const CellProperties Cell::wallProperties = CellProperties('0',
  Colors::wall, Cell::cellSize * 0.0, SQUARE, 0);
const CellProperties Cell::corridorProperties = CellProperties('.',
  Colors::corridor, Cell::cellSize * 0.0, SQUARE, 0);
const CellProperties Cell::foodProperties = CellProperties('*',
  Colors::food, Cell::cellSize * 0.4, CIRCLE, Cell::cellSize * 0.15);
const CellProperties Cell::playerProperties = CellProperties('p',
  Colors::player, Cell::cellSize * 0.3, CIRCLE, Cell::cellSize * 0.3);
const CellProperties Cell::enemyProperties = CellProperties('e',
  Colors::enemy, Cell::cellSize * 0.3, CIRCLE, Cell::cellSize * 0.3);

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

// Getters
float Cell::getX(){ return x; }

float Cell::getY(){ return y; }

bool Cell::isVisited(){ return visited; }

Cell * Cell::getUp(){ return up; }

Cell * Cell::getDown(){ return down; }

Cell * Cell::getLeft(){ return left; }

Cell * Cell::getRight(){ return right; }

CellType Cell::getType(){ return cellType; }

char Cell::getSymbol(){ return getProperties(cellType).symbol; }

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

void Cell::eat(){
    cellType = CORRIDOR;
}

bool Cell::hasFood(){ return cellType == FOOD; }

void Cell::draw(){
    draw(0, 0);
}

void Cell::draw(int transalationX, int transalationY){
    Color color     = getProperties(getType()).color;
    ShapeType shape = getProperties(cellType).shape;

    glColor3f(color.red, color.green, color.blue);
    if (shape == CIRCLE) {
        drawCircle(cellType, transalationX, transalationY);
    } else if (shape == SQUARE) {
        drawSquare(cellType, transalationX, transalationY);
    }
} // draw

void Cell::drawCircle(CellType cellType, int transalationX, int transalationY){
    int radius      = getProperties(cellType).radius;
    int rep         = 50;
    GLfloat twicePi = 2.0f * M_PI;

    float x = ((getY() + 1) * Cell::cellSize) - Cell::cellSize / 2.0 + transalationX;
    float y = ((getX() + 1) * Cell::cellSize) - Cell::cellSize / 2.0 + transalationY;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i < rep; i++) {
        glVertex2f(
          x + (radius * cos(i * twicePi / rep)),
          y + (radius * sin(i * twicePi / rep))
        );
    }
    glEnd();
}

void Cell::drawSquare(CellType cellType, int transalationX, int transalationY){
    int padding = getProperties(cellType).padding;

    glBegin(GL_QUADS);

    glVertex2i(getY() * Cell::cellSize + padding + transalationX,
      getX() * Cell::cellSize + padding + transalationY);
    glVertex2i((getY() + 1) * Cell::cellSize - padding + transalationX,
      getX() * Cell::cellSize + padding + transalationY);
    glVertex2i((getY() + 1) * Cell::cellSize - padding + transalationX,
      (getX() + 1) * Cell::cellSize - padding + transalationY);
    glVertex2i(getY() * Cell::cellSize + padding + transalationX,
      (getX() + 1) * Cell::cellSize - padding + transalationY);

    glEnd();
}

CellProperties Cell::getProperties(CellType cellType){
    switch (cellType) {
        case WALL:
            return Cell::wallProperties;

        case CORRIDOR:
            return Cell::corridorProperties;

        case FOOD:
            return Cell::foodProperties;

        case PLAYER:
            return Cell::playerProperties;

        case ENEMY:
            return Cell::enemyProperties;
    }
    return Cell::wallProperties;
}
