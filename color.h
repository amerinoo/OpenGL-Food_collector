/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#ifndef color_h
#define color_h

#include <GL/glut.h>

typedef struct Color{
    const GLfloat red;
    const GLfloat green;
    const GLfloat blue;
    Color(const GLfloat red, const GLfloat green, const GLfloat blue);
} Color;

class Colors{
 public:
    static const Color background;
    static const Color wall;
    static const Color corridor;
    static const Color food;
    static const Color player;
    static const Color enemy;
};
#endif
