/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#ifndef cell_h
#define cell_h
#include <iostream>
#include "drawer.h"
using namespace std;

class Cell{
 public:
    float x, y;
    Drawer drawer;

    // Constructors
    Cell();
    Cell(float, float, CellType);

    // Getters
    float getX();
    float getY();
    bool isVisited();
    Cell* getUp();
    Cell* getDown();
    Cell* getLeft();
    Cell* getRight();
    char getSymbol();
    CellType getType();
    bool hasFood();
    void eat();
    void draw();


    // Setters
    void setX(float);
    void setY(float);
    void setVisited(bool);
    void setUp(Cell*);
    void setDown(Cell*);
    void setLeft(Cell*);
    void setRight(Cell*);
    void setCellType(CellType);

    // Print
    void print();
 protected:
    CellType cellType;
    bool visited;
    Cell *up, *down, *left, *right;
};
#endif
