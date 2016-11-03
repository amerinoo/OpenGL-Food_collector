/*
 * Project name: Food collection
 * Version 1
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#include "corridor.h"

// Constructors
Corridor::Corridor(int a, int b) : Cell(a, b){ }

// Getters
CellType Corridor::getType(){ return CORRIDOR; }

char Corridor::getSymbol(){ return '.'; }
