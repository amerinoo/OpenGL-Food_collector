#ifndef corridor_h
#define corridor_h

#include "cell.h"

class Corridor : public Cell{
 public:
	Corridor(int, int);
    int getType();
    char getSymbol();
};
#endif
