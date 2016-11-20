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

    const GLfloat red;
    const GLfloat green;
    const GLfloat blue;
    Color(const GLfloat red, const GLfloat green, const GLfloat blue);

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
    const int padding;
    const ShapeType shape;
    const int radius;
    CellProperties(const char symbol, const Color color, const int padding,
        const ShapeType,const int radius);
} CellProperties;

class Drawer{
public:
    static const int cellSize;
    int height, width;
    static Drawer& getInstance();
    void draw(CellType, float, float, bool, int=0, int=0);
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
    void printText(float, float, string);
};
#endif
