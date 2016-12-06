/*
 * Project name: Food collection
 * Version 3
 * Student : Albert Eduard Merino Pulido
 */
#ifndef game_h
#define game_h
#include "agent.h"
#include "strategies.h"
#include <list>

class Game{

 public:
    // Constructors
    Game();
	Game(int, int);

	//Getters
	int getHeight();
	int getWidth();

    void draw();
    void resetGame();
    void newGame();
    void pauseGame();
    void integrate(long);
    void integrate(Agent*,long);
    void finish();
    bool playerWin();
    void moveAgent(CellType, Direction);
    void shoot(CellType);

 private:
    void newMap();
 protected:
 	Map map;
    int width, height;
 	Agent* player;
 	Agent* enemy;
    int level;
    bool pause;
};
#endif
