/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#ifndef reflexAgent_h
#define reflexAgent_h
#include "strategy.h"

using namespace std;

class ReflexAgent: public Strategy{
 public:
    // Constructors
    ReflexAgent();
    ReflexAgent(Map);

    // Methods
    Direction getAction(Cell*);
private:
    float evaluationFunction(Cell*,Direction);
    Cell * getNextState(Cell*, Direction);
    double manhattanDistance(Cell*, Cell*);
};
#endif
