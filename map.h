#include <bits/stdc++.h>
#include <vector>
using namespace std;

class Map{
	int width, heigth;
	vector<vector<int> > map;
 public:
	Map(int,int);
	void generate();
	void print();
};
