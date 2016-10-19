#ifndef graphics_h
#define graphics_h
#include <bits/stdc++.h>
#include "map.h"

using namespace std;

void myDisplay();
void myKeyboard(unsigned char, int, int);

class Graphics{

 public:
    static Graphics& getInstance();
    void init(int argc, char * argv[]);

    void setMap(Map);
    int getHeight();
    int getWidth();
    void display();
    void keyboard(unsigned char c, int x, int y);
 private:
     Graphics();
     Graphics(Graphics const&);
     Graphics& operator=(Graphics const&);
 protected:
     Map map;
     int heigth, width;
     int columns, rows;
};
#endif
