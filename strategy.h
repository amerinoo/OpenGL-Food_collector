/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#ifndef strategy_h
#define strategy_h
#include "agent.h"

using namespace std;

class Strategy{
 public:
    // Constructors
    Strategy();
    Strategy(Map);

    Direction getAction(Agent);
private:
    vector<Direction> getLegalActions(Cell*);
    float evaluationFunction(Cell*,Direction);
    Cell * getNextState(Cell*, Direction);
    double manhattanDistance(Cell*, Cell*);
protected:
    Map map;
};
#endif
