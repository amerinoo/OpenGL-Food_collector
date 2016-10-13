#include <bits/stdc++.h>
#include "cell.h"
#include "corridor.h"
#include "wall.h"

using namespace std;

class Map{
	int width, heigth;
	vector<vector<Cell*> > map;
 public:
	Map(int, int);
	void generate();
	void print();
 private:
 	void populationCells();
 	void connectCells();
 	Cell* connect(Cell *);

 	Wall* copyToWall(Cell *);
 	Corridor* copyToCorridor(Cell *);

	void outside();

	void putWhiteCells();
	vector<vector<Cell *> > getWhitePositionCells();
	Cell* randomCellPosition(vector<vector<Cell *> > visited);

	void inside();
	void mirror();
	void middle();

	bool insideCondition(Cell *c);
	Cell* randomDiscoverPath(Cell*);

	int  getRandomDirection();
	bool isValid(int);
	void print(vector<vector<Cell *> >);
	void test(vector<vector<Cell *> >);
	bool hasValidNeighbours(Cell*);
};
