/*
 * Project name: Food collection
 * Version 1
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

#include "cell.h"
#include "corridor.h"
#include "wall.h"

using namespace std;

enum Direction{
        UP,
        DOWN,
        LEFT,
        RIGHT
};

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

        bool insideCondition(unsigned int, unsigned int);
        void changeToCorridor(Cell *);
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