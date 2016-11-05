/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#ifndef cell_h
#define cell_h
#include <iostream>
#include <GL/glut.h>
#include "color.h"
using namespace std;

enum CellType{
    CELL,
    WALL,
    CORRIDOR,
    FOOD,
    AGENT,
    PLAYER,
    ENEMY
};

typedef struct CellProperties{
    const char symbol;
    const Color color;
    const int padding;
    CellProperties(const char symbol, const Color color, const int padding);
} CellProperties;

class Cell{
 public:
    static const int cellHeigth;
    static const int cellWidth;

    static const CellProperties wallProperties;
    static const CellProperties corridorProperties;
    static const CellProperties foodProperties;
    static const CellProperties playerProperties;
    static const CellProperties enemyProperties;
    // Constructors
    Cell();
    Cell(int, int, CellType);

    // Getters
    int getX();
    int getY();
    bool isVisited();
    Cell* getUp();
    Cell* getDown();
    Cell* getLeft();
    Cell* getRight();
    char getSymbol();
    virtual CellType getType();
    virtual bool hasFood();
    virtual void eat();
    void draw();


    // Setters
    void setVisited(bool);
    void setUp(Cell*);
    void setDown(Cell*);
    void setLeft(Cell*);
    void setRight(Cell*);
    void setCellType(CellType);

    // Print
    void print();
 private:
    CellProperties getProperties();
 protected:
    CellType cellType;
    int x, y;
    bool visited;
    Cell *up, *down, *left, *right;
};
#endif
