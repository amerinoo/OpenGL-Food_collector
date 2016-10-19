#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <fstream>
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
 	void populationCells();
 	void connectCells();
 	void connect(Cell *);

    void inside();
    void middle();
    void inferiorRandom();
    bool randomLeftRightInferior(Cell *);
    void middleRandom();
    bool randomLeftRightMiddle(Cell * );
    void mirror();

    bool insideCondition(int, int);
    void changeToCorridor(Cell *);
	vector<vector<Cell *> > getWhitePositionCells();
	Cell* randomCellPosition(vector<vector<Cell *> > visited);
	Cell* randomDiscoverPath(Cell*);

    void getMapFromFile(char*);
	void print(vector<vector<Cell *> >);
 protected:
	 int width, heigth;
	 vector<vector<Cell*> > map;
	 vector<vector<Cell *> > visited;
};
