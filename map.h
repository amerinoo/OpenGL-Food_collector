/*
 * Project name: Food collection
 * Version 3
 * Student : Albert Eduard Merino Pulido
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


using namespace std;

class Map{
 public:
     static const int initX;
     static const int initY;

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
    vector<Cell*> getFood();
    bool hasFood();
    void eat();
    vector<Direction> getLegalActions(Cell*);

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
        int totalFood;

};
#endif
