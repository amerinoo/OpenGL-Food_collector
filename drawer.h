/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#ifndef drawer_h
#define drawer_h
#include <cmath>
#include "enums.h"
#include <GL/glut.h>

typedef struct Color{

    static const Color background;
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

    Drawer();
    void draw(CellType, float, float, bool);
    void draw(CellType, float, float, int, int);
    CellProperties getProperties(CellType);
private:
    void drawSquare(CellType, float, float, int, int);
    void drawCircle(CellType, float, float, int, int);
};
#endif
