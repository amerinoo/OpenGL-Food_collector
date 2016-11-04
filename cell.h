/*
 * Project name: Food collection
 * Version 1
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#ifndef cell_h
#define cell_h
#include <iostream>
#include <GL/glut.h>
using namespace std;

enum CellType{
    CELL,
    WALL,
    CORRIDOR
};

class Cell{
 public:
    static const int cellHeigth;
    static const int cellWidth;
    // Constructors
    Cell(int, int);

    // Getters
    int getX();
    int getY();
    bool isVisited();
    Cell** getUp();
    Cell** getDown();
    Cell** getLeft();
    Cell** getRight();
    virtual char getSymbol();
    virtual CellType getType();
    virtual bool hasFood();
    virtual void eat();
    virtual void draw(int,int);


    // Setters
    void setVisited(bool);
    void setUp(Cell**);
    void setDown(Cell**);
    void setLeft(Cell**);
    void setRight(Cell**);

    // Print
    void printCell();

    protected:
    Cell **up, **down, **left, **right;
    int x, y;
    bool visited;
};
#endif
