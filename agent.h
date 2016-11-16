/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#ifndef agent_h
#define agent_h
#include <cmath>
#include "strategy.h"
using namespace std;

class Agent{
 public:
     static const int duration;
    // Constructors
    Agent();
    Agent(CellType,Cell*,Strategy*);

    // Getters
    Strategy* getStrategy();
    int getScore();
    State getState();
    Cell* getCurrentPosition();
    Cell* getNextPosition();
    Direction getDirection();
    void draw();

    // Setters
    void setPosition(Cell*);
    void setDirection(Direction);
    void setNextDirection(Direction);

    //Methods
    void goInitPosition();
    void initMovement(Direction, int);
    bool integrate(long);
    void eat();
    void move();
    void tryNextDirection();

 protected:
    Strategy* strategy;
    CellType cellType;
    int score;
    Cell* initPosition;
    Cell* currentPosition;
    Cell* nextPosition;

    State state;
    Direction currentDirection;
    Direction nextDirection;
    float transalationX, transalationY;
    float vx, vy; // Velocity vector
    long time_remaining;
};
#endif
