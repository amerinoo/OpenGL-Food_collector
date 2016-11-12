/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
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
};
#endif
