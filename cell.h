/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#ifndef cell_h
#define cell_h
#include <iostream>
#include <cmath>
#include <GL/glut.h>
using namespace std;

enum CellType{
    WALL,
    CORRIDOR,
    FOOD,
    PLAYER,
    ENEMY
};

enum State{
    MOVE,
    QUIET
};

enum ShapeType{
    SQUARE,
    CIRCLE
};

enum Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};
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
    const char symbol;
    const Color color;
    const int padding;
    const ShapeType shape;
    const int radius;
    CellProperties(const char symbol, const Color color, const int padding,
        const ShapeType,const int radius);
} CellProperties;

class Cell{
 public:
    static const int cellSize;

    static const CellProperties wallProperties;
    static const CellProperties corridorProperties;
    static const CellProperties foodProperties;
    static const CellProperties playerProperties;
    static const CellProperties enemyProperties;

    float x, y;

    // Constructors
    Cell();
    Cell(float, float, CellType);

    // Getters
    float getX();
    float getY();
    bool isVisited();
    Cell* getUp();
    Cell* getDown();
    Cell* getLeft();
    Cell* getRight();
    char getSymbol();
    CellType getType();
    bool hasFood();
    void eat();
    void draw();
    void draw(int, int);


    // Setters
    void setX(float);
    void setY(float);
    void setVisited(bool);
    void setUp(Cell*);
    void setDown(Cell*);
    void setLeft(Cell*);
    void setRight(Cell*);
    void setCellType(CellType);

    // Print
    void print();

 private:
    void drawSquare(CellType, int, int);
    void drawCircle(CellType, int, int);
 protected:
    CellType cellType;
    bool visited;
    Cell *up, *down, *left, *right;
    CellProperties getProperties(CellType cellType);
};
#endif
