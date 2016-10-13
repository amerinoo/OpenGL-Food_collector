#include "cell.h"
using namespace std;

Cell::Cell(int a, int b){
    x       = a;
    y       = b;
    visited = false;

    //setType(-1);

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

void Cell::setType(int k){
    type = k;
}

int Cell::getType(){
    return -1;
}

/*vector<Cell *> Cell::getNeighbours(){
    return neighbours;
}*/

void Cell::toString(){
    cout << getX() << getY() << endl;
}
