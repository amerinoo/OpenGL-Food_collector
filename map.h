#include <bits/stdc++.h>
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
    Map();
 	Map(int, int);
    Map(char*);
 	void generate();
    int getHeigth();
    int getWidth();
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

	void inferiorRandom();
	bool randomLeftRightInferior(Cell *);

	void middleRandom();
	bool randomLeftRightMiddle(Cell * );

	void middle();

	bool insideCondition(int, int);
	Cell* randomDiscoverPath(Cell*);

    void getMapFromFile(char*);

	void print(vector<vector<Cell *> >);
 protected:
	 int width, heigth;
	 vector<vector<Cell*> > map;
	 vector<vector<Cell *> > visited;
};
