#ifndef wall_h
#define wall_h

#include "cell.h"

class Wall : public Cell{
 public:
	Wall(int, int);
    CellType getType();
    char getSymbol();
};
#endif
