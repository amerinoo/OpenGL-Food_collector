/*
 * Project name: Food collection
 * Version 4
 * Student : Albert Eduard Merino Pulido
 */
#ifndef graphics_h
#define graphics_h
#include <GL/glut.h>
#include <cmath>
#include <cstring>
#include <iostream>
#include "game.h"
#include "drawer.h"
#include "arduinoSerial.h"
#include "textureLoader.h"

using namespace std;

void myDisplay();
void myKeyboard(unsigned char, int, int);
void mySpecial(int, int, int);
void myIdle();

class Graphics {
public:

    // Getters
    static Graphics& getInstance();
    int getHeight();
    int getWidth();
    int getMaxHeight();
    int getMaxWidth();

    // Setters
    void setGame(Game);
    void setArduinoSerial(ArduinoSerial *);

    // Methods
    void init(int argc, char * argv[]);
    void start();
    void display();
    void positionObserver(float, float, int);
    void keyboard(unsigned char, int, int);
    void special(int, int, int);
    void idle();
    void serialRead();
    void parseData(char *);
private:
    // Constructors
    Graphics();
    Graphics(Graphics const&);
    Graphics& operator = (Graphics const&);
protected:
    Game game;
    ArduinoSerial * serial;
    int height, width;
    long last_t;
    static const char * windowTitle;
    int anglealpha, anglebeta;
    int fd;
};
#endif // ifndef graphics_h
