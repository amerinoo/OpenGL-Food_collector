#include <iostream>
#include <GL/glut.h>
#include "graphics.h"
using namespace std;
void
init(int argc, char * argv[], int HEIGHT, int WIDTH);
void
display();

Graphics graphics;

int main(int argc, char * argv[]){
    int heigth;
    int width;

    if (argc < 3) {
        heigth = 10;
        width  = 22;
    } else {
        heigth = atoi(argv[1]);
        width  = atoi(argv[2]);
    }
    Map map(heigth, width);

    map.generate();
    map.print();

    graphics = Graphics(map);
    init(argc, argv, graphics.getHeight(), graphics.getWidth());
    return 0;
}

void init(int argc, char * argv[], int HEIGHT, int WIDTH){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Food collection");

    glutDisplayFunc(display);

    glMatrixMode(GL_PROJECTION);
    int left   = 0;
    int bottom = HEIGHT - 1;
    int right  = WIDTH - 1;
    int top    = 0;
    gluOrtho2D(left, right, bottom, top);

    glutMainLoop();
}

void display(){ graphics.display(); }
