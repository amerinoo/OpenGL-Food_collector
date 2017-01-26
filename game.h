/*
 * Project name: Food collection
 * Version 4
 * Student : Albert Eduard Merino Pulido
 */
#ifndef game_h
#define game_h
#include "agent.h"
#include "strategies.h"
#include <list>

class Game {
public:
    // Constructors
    Game();
    Game(int, int, float, StrategyType, StrategyType);

    // Getters
    int getHeight();
    int getWidth();
    bool isPaused();

    void draw();
    void drawText(const char *, bool);
    void resetGame();
    void newGame();
    Strategy * getStrategyByType(CellType, StrategyType);
    void pauseGame();
    void integrate(long);
    void integrate(Agent *, long);
    void finish();
    bool playerWin();
    void showGameResults(bool);
    void moveAgent(CellType, Direction);
    void shoot(CellType);

private:
    void newMap();
protected:
    int height, width;
    Agent * player;
    Agent * enemy;
    int level;
    bool pause;
    float seed;
    StrategyType strategyTypePlayer;
    StrategyType strategyTypeEnemy;
    Map * map;
};
#endif // ifndef game_h
