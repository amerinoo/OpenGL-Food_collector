/*
 * Project name: Food collection
 * Version 4
 * Student : Albert Eduard Merino Pulido
 */
#ifndef cell_h
#define cell_h
#include <iostream>
#include "drawer.h"
using namespace std;

class Cell {
public:
    float x, y;

    // Constructors
    Cell();
    Cell(float, float, CellType);
    bool operator == (Cell *);

    // Getters
    float getX();
    float getY();
    float getKey();
    bool isVisited();
    Cell * getUp();
    Cell * getDown();
    Cell * getLeft();
    Cell * getRight();
    char getSymbol();
    CellType getType();
    bool hasFood();
    bool isWall();
    bool isCorridor();
    void eat();
    void draw();


    // Setters
    void setX(float);
    void setY(float);
    void setVisited(bool);
    void setUp(Cell *);
    void setDown(Cell *);
    void setLeft(Cell *);
    void setRight(Cell *);
    void setCellType(CellType);

    // Print
    void print();
protected:
    CellType cellType;
    bool visited;
    Cell * up, * down, * left, * right;
};
#endif // ifndef cell_h
