/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#include "graphics.h"

using namespace std;

const char * Graphics::windowTitle = "Food collection - Merino&Kin";

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

int Graphics::getMaxHeigth(){ return glutGet(GLUT_SCREEN_HEIGHT) / Cell::cellSize; }

int Graphics::getMaxWidth(){ return glutGet(GLUT_SCREEN_WIDTH) / Cell::cellSize; }

// Setters
void Graphics::setGame(Game g){ game = g; }

// Methods
void Graphics::init(int argc, char * argv[]){
    glutInit(&argc, argv);
}

void Graphics::start(){
    heigth = game.getHeight() * Cell::cellSize;
    width  = game.getWidth() * Cell::cellSize;
    last_t = 0;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, heigth);
    glutCreateWindow(Graphics::windowTitle);

    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecial);
    glutIdleFunc(myIdle);

    glMatrixMode(GL_MODELVIEW);
    gluOrtho2D(0, width - 1, heigth - 1, 0);

    glutMainLoop();
}

void Graphics::display(){
    glClearColor(Cell::background.red, Cell::background.green, Cell::background.blue, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    game.draw();

    glutSwapBuffers();
} // display

void Graphics::keyboard(unsigned char c, int x, int y){
    CellType cellType = PLAYER;

    if (c == 'r') game.newGame();
    else if (c == 'w') game.moveAgent(cellType, UP);
    else if (c == 's') game.moveAgent(cellType, DOWN);
    else if (c == 'a') game.moveAgent(cellType, LEFT);
    else if (c == 'd') game.moveAgent(cellType, RIGHT);

    glutPostRedisplay();
}

void Graphics::special(int key, int x, int y){
    CellType cellType = PLAYER;

    switch (key) {
        case GLUT_KEY_UP:
            game.moveAgent(cellType, UP);
            break;
        case GLUT_KEY_DOWN:
            game.moveAgent(cellType, DOWN);
            break;
        case GLUT_KEY_LEFT:
            game.moveAgent(cellType, LEFT);
            break;
        case GLUT_KEY_RIGHT:
            game.moveAgent(cellType, RIGHT);
            break;
    }
    glutPostRedisplay();
}

void Graphics::idle(){
    long t = glutGet(GLUT_ELAPSED_TIME);

    if (last_t == 0) {
        last_t = t;
    } else {
        game.integrate(t - last_t);
        last_t = t;
    }

    glutPostRedisplay();
}

void myDisplay(){ Graphics::getInstance().display(); }

void myKeyboard(unsigned char c, int x, int y){ Graphics::getInstance().keyboard(c, x, y); }

void mySpecial(int key, int x, int y){ Graphics::getInstance().special(key, x, y); }

void myIdle(){ Graphics::getInstance().idle(); }
