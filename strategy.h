/*
 * Project name: Food collection
 * Version 4
 * Student : Albert Eduard Merino Pulido
 */
#ifndef strategy_h
#define strategy_h
#include "map.h"
#include <climits>
#include <queue>
#include <map>

using namespace std;

typedef struct Node {
    Cell *        state;
    struct Node * parent;
    Direction     action;
    Node();
    Node(Cell *, Node *, Direction);

    vector<Direction> path();
} Node;

class Strategy {
public:
    // Constructors
    Strategy();
    Strategy(Map *, CellType agent);

    Map * getGameState();
    virtual Direction getAction();
    virtual void final(Map state);
    Direction randomChoice(vector<Direction> );
    vector<Direction> getLegalActions(Cell *);
    float getDistance(Map, Cell *, Cell *);
    float manhattanDistance(Cell *, Cell *);
    vector<Direction> blindSearchGraph(Map, Cell *, Cell *);

protected:
    Map * gameState;
    CellType agent1;
    CellType agent2;
};
#endif // ifndef strategy_h
