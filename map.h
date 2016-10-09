#include <bits/stdc++.h>
#include "cell.h"
using namespace std;

class Map{
	int width, heigth;
	vector<vector<Cell*> > map;
 public:
	Map(int, int);
	void generate();
	void print();
 private:
	 void outside();
	 void inside();
	 void mirror();
	 void middle();
	 int getRandom();
};
