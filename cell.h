#ifndef cell_h
#define cell_h
#include <bits/stdc++.h>
using namespace std;
enum CellType{
    CELL,
    WALL,
    CORRIDOR
};
class Cell{

 public:
    Cell(int, int);
    int getX();
    int getY();
    bool isVisited();
    void setVisited(bool b);
    virtual CellType getType();
    virtual char getSymbol();
    void toString();
    Cell **top, **left, **right, **bottom;
 protected:
     int x, y;
     bool visited;
};
#endif
