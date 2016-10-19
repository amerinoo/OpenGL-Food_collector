#include <GL/glut.h>
#include "graphics.h"

using namespace std;

// Constructors
Graphics::Graphics(){ }

// Getters
Graphics& Graphics::getInstance(){
    static Graphics instance;

    return instance;
}

// Getters
int Graphics::getHeight(){ return heigth; }

int Graphics::getWidth(){ return width; }

// Setters
void Graphics::setMap(Map m){ map = m; }

// Methods
void Graphics::init(int argc, char * argv[]){
    columns = map.getWidth();
    rows    = map.getHeigth();
    heigth  = map.getHeigth() * 20;
    width   = map.getWidth() * 20;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(width, heigth);
    glutCreateWindow("Food collection");

    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(myKeyboard);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, width - 1, heigth - 1, 0);

    glutMainLoop();
}

void Graphics::display(){
    vector<vector<Cell *> > m = map.getMap();

    glClearColor(0, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    int a = width / columns;
    int b = heigth / rows;

    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            if (m[j][i]->getType() == CORRIDOR) {
                glBegin(GL_QUADS);
                glColor3f(1, 1, 1);

                glVertex2i(i * a, j * b);             // esquerra dalt
                glVertex2i((i + 1) * a, j * b);       // dreta dalt
                glVertex2i((i + 1) * a, (j + 1) * b); // dreta baix
                glVertex2i(i * a, (j + 1) * b);       // esquerra baix

                glEnd();
            }
        }
    }
    glutSwapBuffers();
} // display

void Graphics::keyboard(unsigned char c, int x, int y){
    if (c == 'r') {
        Map m = Map(map.getHeigth(), map.getWidth());
        setMap(m);
        glutPostRedisplay();
    }
}

void myDisplay(){ Graphics::getInstance().display(); }

void myKeyboard(unsigned char c, int x, int y){ Graphics::getInstance().keyboard(c, x, y); }
