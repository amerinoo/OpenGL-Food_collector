#include <bits/stdc++.h>
#include "map.h"

using namespace std;

class Graphics{

 public:
    Graphics();
	Graphics(Map);
    Graphics(char *);
	void display();
    int getHeight();
    int getWidth();
 private:
    Map getMapFromFile(char*);
    void init(Map);
 protected:
     Map map;
     int HEIGHT, WIDTH;
     int COLUMNS, ROWS;
};
