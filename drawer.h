/*
 * Project name: Food collection
 * Version 3
 * Student : Albert Eduard Merino Pulido
 */
#ifndef drawer_h
#define drawer_h
#include <cmath>
#include <GL/glut.h>
#include <string>
#include <sstream>
#include "enums.h"

using namespace std;

typedef struct Color{

    static const Color background;
    static const Color text;
    static const Color wall;
    static const Color corridor;
    static const Color food;
    static const Color player;
    static const Color enemy;
    static const Color tank;

    const GLfloat red1;
    const GLfloat green1;
    const GLfloat blue1;
    const GLfloat red2;
    const GLfloat green2;
    const GLfloat blue2;
    Color(const GLfloat red1, const GLfloat green1, const GLfloat blue1,
      const GLfloat red2=0, const GLfloat green2=0, const GLfloat blue2=0);

    GLfloat RGBToGlut(int);
} Color;

typedef struct CellProperties{

    static const CellProperties wall;
    static const CellProperties corridor;
    static const CellProperties food;
    static const CellProperties player;
    static const CellProperties enemy;

    const char symbol;
    const Color color;
    CellProperties(const char symbol, const Color color);
} CellProperties;

class Drawer{
public:
    static const int cellSize;
    static const GLfloat x;
    static const GLfloat y;
    static const GLfloat z;
    static const GLdouble r;
    int height, width;
    static Drawer& getInstance();
    void draw(CellType, float, float, bool,Direction=NONE, int=0, int=0);
    CellProperties getProperties(CellType);

    void setHeight(int);
    void setWidth(int);
    void printScore(int, int);
    void printLevel(int);
private:
    // Constructors
    Drawer();
    Drawer(Drawer const&);
    Drawer& operator=(Drawer const&);
    void drawWall();
    void drawCorridor();
    void drawFood();
    void drawTank(CellType,Direction);
    void drawCylinder(GLdouble, GLdouble, Color);
    void drawHead(Color);
    void drawCube(Color);
    void printText(float, float, string);
};
#endif
