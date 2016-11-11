/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#ifndef map_h
#define map_h
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <stack>
#include <list>

#include "cell.h"
#include "agent.h"
#include "player.h"
#include "enemy.h"


using namespace std;

class Map{
 public:
    // Constructors
    Map();
 	Map(int, int);
    Map(char*);

    // Getters
    int getHeigth();
    int getWidth();
    vector<vector<Cell*> > getMap();

    // Methods
    void generate();
    Cell* initPlayer();
    Cell* initEnemy();

    Direction getNextPosition(Enemy);
    vector<Direction> getLegalActions(Cell*);
    float evaluationFunction(Enemy,Cell*,Direction);
    Cell * getNextState(Cell*, Direction);
    vector<Cell*> getFood();
    double manhattanDistance(Cell*, Cell*);


    // Print
 	void print();

    private:
     	void initCells();
        void connect(Cell *);
     	void connectCells();
        void inside();
        void middle();
        void inferiorRandom();
        void middleRandom();
        void openRandom(Cell *, vector<Direction>);
        void mirror();
        void initMap();

        bool insideCondition(unsigned int, unsigned int);
    	void initWhitePositionCells();
    	Cell* randomDiscoverPath(Cell*);

        void getMapFromFile(char*);
    	void print(vector<vector<Cell *> >);

    protected:
        int width, heigth;
        vector<vector<Cell*> > map;
        vector<vector<Cell *> > visited;

};
#endif
