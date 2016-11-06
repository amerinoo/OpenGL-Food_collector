/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#ifndef game_h
#define game_h
#include "map.h"

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
    void moveAgent(CellType, Direction);
 private:
    void newMap();

 protected:
 	Map map;
    int width, height;
 	Player player;
 	Enemy enemy;
};
#endif
