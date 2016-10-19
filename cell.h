#ifndef cell_h
#define cell_h
#include <iostream>
using namespace std;

enum CellType{
    CELL,
    WALL,
    CORRIDOR
};

class Cell{
 public:
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
