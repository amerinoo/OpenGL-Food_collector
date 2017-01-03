/*
 * Project name: Food collection
 * Version 4
 * Student : Albert Eduard Merino Pulido
 */
#ifndef expectimaxAgent_h
#define expectimaxAgent_h
#include "strategy.h"

using namespace std;

class ExpectimaxAgent : public Strategy {
public:
    static const int c1;
    static const int c2;
    // Constructors
    ExpectimaxAgent();
    ExpectimaxAgent(Map *, int = 4);

    // Methods
    Direction getAction();

private:
    float maxValue(Map, CellType, int);
    float minValue(Map, CellType, int);
    Direction expectimaxDecision();
    Map result(Map, CellType, Direction);
    bool terminalTest(Map, int);
    float utility(Map);
    float evaluationFunction(Map);

    int depth;
    int best;
    bool alarm;
    vector<Direction> bestDirections;
};
#endif // ifndef expectimaxAgent_h
