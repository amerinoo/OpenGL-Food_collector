/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#ifndef wall_h
#define wall_h

#include "cell.h"

class Wall : public Cell{
 public:
    // Constructors
	Wall(int, int);

    // Getters
    CellType getType();
    char getSymbol();
    void draw();
};
#endif
