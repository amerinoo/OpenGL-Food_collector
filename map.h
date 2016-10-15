#include <bits/stdc++.h>
#include "cell.h"
#include "corridor.h"
#include "wall.h"

using namespace std;

class Map{

 public:
    Map();
 	Map(int, int);
    Map(vector<vector<Cell*> >);
 	void generate();
    vector<vector<Cell*> > getMap();
 	void print();
 private:
 	void populationCells();
 	void connectCells();
 	void connect(Cell *);

 	void changeToCorridor(Cell *);

	vector<vector<Cell *> > getWhitePositionCells();
	Cell* randomCellPosition(vector<vector<Cell *> > visited);

	void inside();
	void mirror();
	void middle();

	bool insideCondition(int, int);
	Cell* randomDiscoverPath(Cell*);

	void print(vector<vector<Cell *> >);
 protected:
	 int width, heigth;
	 vector<vector<Cell*> > map;
	 vector<vector<Cell *> > visited;
};
