/*
 * Project name: Food collection
 * Version 4
 * Student : Albert Eduard Merino Pulido
 */
#ifndef drawer_h
#define drawer_h
#include <cmath>
#include <GL/glut.h>
#include <string>
#include <utility>
#include <sstream>
#include "enums.h"

using namespace std;

typedef struct Color {
    static const Color background;
    static const Color text;
    static const Color wall;
    static const Color corridor;
    static const Color food;
    static const Color player;
    static const Color enemy;
    static const Color tank;
    static const Color bullet;

    static const Color texture;
    static const Color light_position;
    static const Color light_ambient;
    static const Color light_diffuse;
    static const Color light_specular;

    static const Color light_tank_ambient;
    static const Color light_tank_diffuse;

    const GLfloat      red1;
    const GLfloat      green1;
    const GLfloat      blue1;
    const GLfloat      alpha1;
    const GLfloat      red2;
    const GLfloat      green2;
    const GLfloat      blue2;
    const GLfloat      alpha2;

    Color(const GLfloat red1, const GLfloat green1, const GLfloat blue1, const GLfloat alpha1 = 1,
      const GLfloat red2 = 0, const GLfloat green2 = 0, const GLfloat blue2 = 0, const GLfloat alpha2 = 1);

    GLfloat RGBToGlut(int);

    GLfloat * toArray1();
    GLfloat * toArray2();
} Color;

typedef struct CellProperties {
    static const CellProperties wall;
    static const CellProperties corridor;
    static const CellProperties food;
    static const CellProperties player;
    static const CellProperties enemy;
    static const CellProperties bullet;

    const char                  symbol;
    const Color                 color;
    CellProperties(const char symbol, const Color color);
} CellProperties;

class Drawer {
public:
    static const int cellSize;
    static const GLfloat x;
    static const GLfloat y;
    static const GLfloat z;
    static const GLdouble r;
    static const GLint slices;
    static const GLint stacks;
    static const GLfloat spot_cutoff;
    int height, width;
    static Drawer& getInstance();
    void draw(CellType, float, float, bool, Direction = NONE, int = 0, int = 0, int = 0);
    CellProperties getProperties(CellType);

    void setHeight(int);
    void setWidth(int);
    void printTitle(const char *);
    void printScore(int, int);
    void printLevel(int);
    void printVelocity(int);
    void printFood(int);
    void printArduino(bool);
private:
    // Constructors
    Drawer();
    Drawer(Drawer const&);
    Drawer& operator = (Drawer const&);
    void drawWall();
    void drawCorridor();
    void drawSphere(CellType);
    void drawTank(CellType, Direction, float);
    void drawCanon(GLdouble, GLdouble, Color);
    void drawWheel(GLdouble, GLdouble, Color);
    void drawHead(Color);
    void drawCube(Color);
    void printText(float, float, string, void *);
    void configureLight(CellType, Direction);
    GLfloat * getSpotDirection(Direction);
};
#endif // ifndef drawer_h
