/*
 * Project name: Food collection
 * Version 1
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#ifndef corridor_h
#define corridor_h

#include "cell.h"

class Corridor : public Cell{
 	public:
    // Constructors
	Corridor(int, int);

    // Getters
    CellType getType();
    char getSymbol();
};
#endif
