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
};
#endif
