#ifndef cell_h
#define cell_h
#include <bits/stdc++.h>

class Cell{
	int x, y;
 public:
	Cell(int, int);
    int getX();
    int getY();
	virtual int type();
};
#endif
