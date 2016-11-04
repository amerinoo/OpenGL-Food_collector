/*
 * Project name: Food collection
 * Version 1
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
	Map getMap();

    void draw();
    void newMap(int,int);
    void newMap();
 protected:
 	Map map;
};
#endif