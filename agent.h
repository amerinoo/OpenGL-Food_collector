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
    float getX();
    float getY();
    int getPoints();
    State getState();
    Direction getDirection();
    void draw();

    // Setters
    void setPosition(Cell*);

    //Methods
    virtual void goInitPosition();
    void initMovement(Direction, int);
    void integrate(long);
    void eat();
    void move(Direction);

 protected:
    Cell* position;
    Cell* nextPosition;
    Cell* initPosition;
    Direction direction;
    int points;
    State state;
    float transalationX, transalationY;
    float vx, vy; // Velocity vector
    long time_remaining;
};
#endif
