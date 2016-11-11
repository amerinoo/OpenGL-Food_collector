/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#ifndef agent_h
#define agent_h
#include <cmath>
#include "cell.h"
using namespace std;

enum State{
    MOVE,
    QUIET
};

class Agent: public Cell{
 public:
     static const int initX;
     static const int initY;
     static const int duration;
    // Constructors
    Agent();
    Agent(Cell*);

    // Getters
    int getScore();
    State getState();
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
    Cell* position;
    Cell* nextPosition;
    Cell* initPosition;
    Direction direction;
    Direction nextDirection;
    int score;
    State state;
    float transalationX, transalationY;
    float vx, vy; // Velocity vector
    long time_remaining;
};
#endif
