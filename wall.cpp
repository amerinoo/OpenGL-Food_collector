#include "wall.h"

Wall::Wall(int a, int b)
    : Cell(a, b){ }

int Wall::type(){
    return 1;
}
