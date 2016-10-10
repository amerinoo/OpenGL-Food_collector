#include "cell.h"
using namespace std;

Cell::Cell(int a, int b){
    x       = a;
    y       = b;
    visited = false;

    top = NULL;
    bottom = NULL;
    left = NULL;
    right = NULL;
}

int Cell::getX(){
    return x;
}

int Cell::getY(){
    return y;
}

bool Cell::isVisited(){
    return visited;
}

void Cell::setVisited(bool b){
    visited = b;
}

/*vector<Cell *> Cell::getNeighbours(){
    return neighbours;
}*/

int Cell::type(){
    return -1;
}

void Cell::toString(){
    cout << getX() << getY() << endl;
}
