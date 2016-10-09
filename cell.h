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
    vector<Cell*> getNeighbours();
	virtual int type();
    void toString();
protected:
		int x, y;
		bool visited;
        vector<Cell*> neighbours;
};
#endif
