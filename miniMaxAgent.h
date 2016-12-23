/*
 * Project name: Food collection
 * Version 4
 * Student : Albert Eduard Merino Pulido
 */
#ifndef miniMaxAgent_h
#define miniMaxAgent_h
#include "strategy.h"

using namespace std;

class MinimaxAgent : public Strategy {
public:
    // Constructors
    MinimaxAgent();
    MinimaxAgent(Map);

    // Methods
    Direction getAction(Cell *);

private:
    vector<Direction> getLegalActions(Cell *);
    float evaluationFunction(Cell *, Direction);
    Cell * getNextState(Cell *, Direction);
    double manhattanDistance(Cell *, Cell *);
};
#endif // ifndef miniMaxAgent_h
