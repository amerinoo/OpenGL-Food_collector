/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#ifndef game_h
#define game_h
#include "map.h"
#include "player.h"
#include "enemy.h"

class Game{
 public:
    // Constructors
    Game();
	Game(int, int);

	//Getters
	Map getMap();

    void draw();
    void newMap(int,int);
    void newMap();
 protected:
 	Map map;
 	Player player;
 	Enemy enemy;
};
#endif
