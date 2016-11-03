#ifndef graphics_h
#define graphics_h
#include <GL/glut.h>
#include "map.h"

using namespace std;

void myDisplay();
void myKeyboard(unsigned char, int, int);

class Graphics{
 public:
    // Getters
    static Graphics& getInstance();
    int getHeight();
    int getWidth();
    int getMaxHeigth();
    int getMaxWidth();

    // Setters
    void setMap(Map);

    // Methods
    void init(int argc, char * argv[]);
    void start();
    void display();
    void keyboard(unsigned char, int, int);
 private:
     // Constructors
     Graphics();
     Graphics(Graphics const&);
     Graphics& operator=(Graphics const&);
 protected:
     Map map;
     int heigth, width;
     int columns, rows;

     static const char* windowTitle;
     static const int cellHeigth;
     static const int cellWidth;
};
#endif
