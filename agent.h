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

typedef struct Bullet{
    Cell* position;
    Direction direction;
    bool enable;
    Particle particle;
    Bullet();
    Bullet(Cell* position, Direction direction);
} Bullet;

class Agent{
 public:
     static int agentVelocity;
     static int rotateVelocity;
     static int bulletVelocity;

     static void setVelocity(int);
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
    void moveBullet();
    bool isCrashBullet();
    void crashBullet();
    void eat();
    void move();
    void move(Cell*);
    void crash();
    Translation getTranslation(Direction);
    bool isCrash();
    void rotate();
    void shoot();
    bool canShoot();
    void tryNextDirection();
    Cell* getNextPosition(Direction,Cell*);
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
    Bullet bullet;

    Direction lastDirection;
    Direction currentDirection;
    Direction nextDirection;
};
#endif
