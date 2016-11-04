/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#ifndef graphics_h
#define graphics_h
#include <GL/glut.h>

#include "game.h"

using namespace std;

void myDisplay();
void myKeyboard(unsigned char, int, int);
void mySpecial(int, int, int);

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
    void keyboard(unsigned char, int, int);
    void special(int, int, int);
 private:
     // Constructors
     Graphics();
     Graphics(Graphics const&);
     Graphics& operator=(Graphics const&);
 protected:
     Game game;
     int heigth, width;

     static const char* windowTitle;
};
#endif
