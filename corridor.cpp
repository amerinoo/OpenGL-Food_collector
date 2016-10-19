#include "corridor.h"

// Constructors
Corridor::Corridor(int a, int b) : Cell(a, b){ }


// Getters
CellType Corridor::getType(){ return CORRIDOR; }

char Corridor::getSymbol(){ return '.'; }
