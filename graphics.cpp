/*
 * Project name: Food collection
 * Version 1
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#include "graphics.h"

using namespace std;

const char * Graphics::windowTitle = "Food collection - Merino&Kin";

const int Graphics::cellHeigth = 20;
const int Graphics::cellWidth  = 20;

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

int Graphics::getMaxHeigth(){ return glutGet(GLUT_SCREEN_HEIGHT) / Graphics::cellHeigth; }

int Graphics::getMaxWidth(){ return glutGet(GLUT_SCREEN_WIDTH) / Graphics::cellWidth; }

// Setters
void Graphics::setMap(Map m){ map = m; }

// Methods
void Graphics::init(int argc, char * argv[]){
    glutInit(&argc, argv);
}

void Graphics::start(){
    columns = map.getWidth();
    rows    = map.getHeigth();
    heigth  = map.getHeigth() * Graphics::cellWidth;
    width   = map.getWidth() * Graphics::cellHeigth;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, heigth);
    glutCreateWindow(Graphics::windowTitle);

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

                // left up
                glVertex2i(i * Graphics::cellWidth, j * Graphics::cellHeigth);
                // right up
                glVertex2i((i + 1) * Graphics::cellWidth, j * Graphics::cellHeigth);
                // right down
                glVertex2i((i + 1) * Graphics::cellWidth, (j + 1) * Graphics::cellHeigth);
                // left down
                glVertex2i(i * Graphics::cellWidth, (j + 1) * Graphics::cellHeigth);

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
        m.print();
        glutPostRedisplay();
    }
}

void myDisplay(){ Graphics::getInstance().display(); }

void myKeyboard(unsigned char c, int x, int y){ Graphics::getInstance().keyboard(c, x, y); }
