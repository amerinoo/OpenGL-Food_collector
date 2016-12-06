/*
 * Project name: Food collection
 * Version 3
 * Student : Albert Eduard Merino Pulido
 */
#ifndef strategy_h
#define strategy_h
#include "map.h"

using namespace std;

class Strategy{
 public:
    // Constructors
    Strategy();
    Strategy(Map*);

    virtual Direction getAction(Cell*);
    Map* getMap();
protected:
    Map* map;
};
#endif
