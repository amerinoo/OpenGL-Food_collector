/*
 * Project name: Food collection
 * Version 3
 * Student : Albert Eduard Merino Pulido
 */
#ifndef agent_h
#define agent_h
#include <cmath>
#include "strategy.h"
#include "particle.h"
using namespace std;

class Agent{
 public:
     static int duration;
     Agent* agent;
    // Constructors
    Agent();
    Agent(CellType, Cell*, Strategy*);

    // Getters
    Strategy* getStrategy();
    int getScore();
    State getState();
    bool isQuiet();
    bool isMove();
    bool isRotate();
    Cell* getCurrentPosition();
    Cell* getNextPosition();
    Direction getDirection();
    void draw();

    // Setters
    void setPosition(Cell*);
    void setDirection(Direction);
    void setNextDirection(Direction);
    void setAgent(Agent*);

    //Methods
    void goInitPosition();
    void initMovement(Direction, int);
    bool integrate(long);
    void eat();
    void move();
    Translation getTranslation(Direction);
    bool isCrash();
    void rotate();
    void shoot();
    void tryNextDirection();
    Cell* getNextPosition(Direction);
 protected:
    Strategy* strategy;
    Map* map;
    CellType cellType;
    Particle particle;
    int score;
    Cell* initPosition;
    Cell* currentPosition;
    Cell* nextPosition;
    bool needRotate;

    Direction lastDirection;
    Direction currentDirection;
    Direction nextDirection;
};
#endif
