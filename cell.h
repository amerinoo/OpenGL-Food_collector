#ifndef cell_h
#define cell_h
#include <bits/stdc++.h>
using namespace std;

class Cell{

 public:
	Cell(int, int);
    int getX();
    int getY();
	bool isVisited();
	void setVisited(bool b);
	void setType(int k);
    //vector<Cell*> getNeighbours();
	Cell **top, **left, **right, **bottom;

	virtual int getType();
    void toString();

	protected:
		int x, y, type;
		bool visited;
        //vector<Cell*> neighbours;
};

#endif
