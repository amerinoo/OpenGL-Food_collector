/*
 * Project name: Food collection
 * Version 4
 * Student : Albert Eduard Merino Pulido
 */
#ifndef strategy_h
#define strategy_h
#include "map.h"
#include <climits>

using namespace std;

class Strategy {
public:
    // Constructors
    Strategy();
    Strategy(Map *);

    Map * getGameState();
    virtual Direction getAction();
    vector<Direction> getLegalActions(Cell *);
    float getDistance(Cell *, Cell *);
    float manhattanDistance(Cell *, Cell *);

protected:
    Map * gameState;
};
#endif // ifndef strategy_h
