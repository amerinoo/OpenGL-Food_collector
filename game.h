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
    void integrate(long);
    void integrate(Agent*,long);
    void moveAgent(CellType, Direction);

 private:
    void newMap();
 protected:
 	Map map;
    int width, height;
 	Agent player;
 	Agent enemy;
    int level;
};
#endif
