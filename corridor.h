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
