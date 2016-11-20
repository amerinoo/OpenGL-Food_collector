/*
 * Project name: Food collection
 * Version 3
 * Student : Albert Eduard Merino Pulido
 */
#ifndef graphics_h
#define graphics_h
#include <GL/glut.h>
#include <cmath>
#include "game.h"
#include "drawer.h"

using namespace std;

void myDisplay();
void myKeyboard(unsigned char, int, int);
void mySpecial(int, int, int);
void myIdle();

class Graphics{
 public:

    // Getters
    static Graphics& getInstance();
    int getHeight();
    int getWidth();
    int getMaxHeigth();
    int getMaxWidth();

    // Setters
    void setGame(Game);

    // Methods
    void init(int argc, char * argv[]);
    void start();
    void display();
    void positionObserver(float, float, int);
    void keyboard(unsigned char, int, int);
    void special(int, int, int);
    void idle();
 private:
     // Constructors
     Graphics();
     Graphics(Graphics const&);
     Graphics& operator=(Graphics const&);
 protected:
     Game game;
     int heigth, width;
     long last_t;
     static const char* windowTitle;
     int anglealpha, anglebeta;
};
#endif
