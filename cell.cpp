#include "cell.h"

Cell::Cell(int a, int b){
    x = a;
    y = b;
}

int Cell::getX(){
    return x;
}

int Cell::getY(){
    return y;
}

int Cell::type(){
    return -1;
}
