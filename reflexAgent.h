/*
 * Project name: Food collection
 * Version 4
 * Student : Albert Eduard Merino Pulido
 */
#ifndef reflexAgent_h
#define reflexAgent_h
#include "strategy.h"

using namespace std;

class ReflexAgent : public Strategy {
public:
    // Constructors
    ReflexAgent();
    ReflexAgent(Map *);

    // Methods
    Direction getAction();
    float evaluationFunction(Map, Direction);
};
#endif // ifndef reflexAgent_h
