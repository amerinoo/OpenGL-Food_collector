/*
 * Project name: Food collection
 * Version 4
 * Student : Albert Eduard Merino Pulido
 */
#ifndef agent_h
#define agent_h
#include <cmath>
#include "strategy.h"
#include "particle.h"
using namespace std;

typedef struct Bullet {
    Cell *    position;
    Direction direction;
    bool      enable;
    Particle  particle;
    Bullet();
    Bullet(Cell * position, Direction direction);
} Bullet;

class Agent {
public:
    static int agentVelocity;
    static int rotateVelocity;
    static int bulletVelocity;

    static void setVelocity(int);
    Agent * agent;
    // Constructors
    Agent();
    Agent(CellType, Cell *, Strategy *);

    // Getters
    Strategy * getStrategy();
    int getScore();
    State getState();
    bool isQuiet();
    bool isMove();
    bool isRotate();
    bool getNeedAction();
    Cell * getCurrentPosition();
    Cell * getNextPosition();
    Direction getDirection();
    void draw();

    // Setters
    void setPosition(Cell *);
    void setDirection(Direction);
    void setNextDirection(Direction);
    void setAgent(Agent *);

    // Methods
    void goInitPosition();
    void initMovement(Direction, int);
    bool integrate(long);
    void moveBullet();
    bool isCrashBullet();
    void crashBullet();
    void eat();
    void move();
    void move(Cell *);
    void crash();
    Translation getTranslation(Direction);
    bool isCrash();
    bool isCrash(CellType agent, Cell * c1, Cell * c2);
    float manhattanDistance(Cell*, Cell*);
    void rotate();
    void shoot();
    bool canShoot();
    void tryNextDirection();
    Cell * getNextPosition(Direction, Cell *);
protected:

    CellType cellType;
    Cell * initPosition;
    Strategy * strategy;
    Map * gameState;
    int score;
    Cell * nextPosition;
    Particle particle;

    bool needRotate;
    Bullet bullet;

    Direction lastDirection;
    Direction currentDirection;
    Direction nextDirection;
};
#endif // ifndef agent_h
