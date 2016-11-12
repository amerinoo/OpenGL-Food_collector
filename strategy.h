/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#ifndef strategy_h
#define strategy_h
#include "map.h"

using namespace std;

class Strategy{
 public:
    // Constructors
    Strategy();
    Strategy(Map);

    virtual Direction getAction(Cell*);
protected:
    Map map;
};
#endif
