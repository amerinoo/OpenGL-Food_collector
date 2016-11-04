/*
 * Project name: Food collection
 * Version 1
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

int Graphics::getMaxHeigth(){ return glutGet(GLUT_SCREEN_HEIGHT) / Cell::cellHeigth; }

int Graphics::getMaxWidth(){ return glutGet(GLUT_SCREEN_WIDTH) / Cell::cellWidth; }

// Setters
void Graphics::setGame(Game g){ game = g; }

// Methods
void Graphics::init(int argc, char * argv[]){
    glutInit(&argc, argv);
}

void Graphics::start(){
    heigth  = game.getMap().getHeigth() * Cell::cellWidth;
    width   = game.getMap().getWidth() * Cell::cellHeigth;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, heigth);
    glutCreateWindow(Graphics::windowTitle);

    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecial);

    //glMatrixMode(GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW);
    gluOrtho2D(0, width - 1, heigth - 1, 0);

    glutMainLoop();
}

void Graphics::display(){

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    game.draw();
    
    glutSwapBuffers();
} // display

void Graphics::keyboard(unsigned char c, int x, int y){
    
    if(c == 'r'){
        game.newMap();
    }else if(c == 'w'){
        cout << "UP" << endl;
    }else if(c == 's'){
        cout << "DOWN" << endl;
    }else if(c == 'a'){
        cout << "RIGHT" << endl;
    }else if(c == 'd'){
        cout << "LEFT" << endl;
    }
    glutPostRedisplay();
}

void Graphics::special(int key, int x, int y){
    switch(key)
    {
    case GLUT_KEY_UP:
        cout << "UP" << endl;
        break;
    case GLUT_KEY_DOWN:
        cout << "DOWN" << endl;
        break;
    case GLUT_KEY_LEFT:
        cout << "RIGHT" << endl;
        break;
    case GLUT_KEY_RIGHT:
        cout << "LEFT" << endl;
        break;
    }
}

void myDisplay(){ Graphics::getInstance().display(); }

void myKeyboard(unsigned char c, int x, int y){ Graphics::getInstance().keyboard(c, x, y); }

void mySpecial(int key, int x, int y){ Graphics::getInstance().special(key, x, y); }
