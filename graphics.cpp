/*
 * Project name: Food collection
 * Version 4
 * Student : Albert Eduard Merino Pulido
 */
#include "graphics.h"

using namespace std;

const char * Graphics::windowTitle = "Food collection";

// Constructors
Graphics::Graphics(){ }

// Getters
Graphics& Graphics::getInstance(){
    static Graphics instance;

    return instance;
}

// Getters
int Graphics::getHeight(){ return height; }

int Graphics::getWidth(){ return width; }

int Graphics::getMaxHeight(){ return glutGet(GLUT_SCREEN_HEIGHT) / Drawer::cellSize; }

int Graphics::getMaxWidth(){ return glutGet(GLUT_SCREEN_WIDTH) / Drawer::cellSize; }

// Setters
void Graphics::setGame(Game g){ game = g; }

void Graphics::setArduinoSerial(ArduinoSerial * s){ serial = s; }

// Methods
void Graphics::init(int argc, char * argv[]){
    glutInit(&argc, argv);
}

void Graphics::start(){
    height     = game.getHeight() * Drawer::cellSize;
    width      = game.getWidth() * Drawer::cellSize;
    last_t     = 0;
    anglealpha = 90;
    anglebeta  = -45; // -45

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, height);
    glutCreateWindow(Graphics::windowTitle);

    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecial);
    glutIdleFunc(myIdle);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);

    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    TextureLoader().loadTextures();
    configureAmbientLight();
    glutMainLoop();
}

void Graphics::display(){
    glClearColor(Color::background.red1, Color::background.green1, Color::background.blue1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width * 0.5, width * 0.5, -height * 0.5, height * 0.5, 50, 2000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    positionObserver(anglealpha, anglebeta, 450);

    game.draw();
    game.drawText(windowTitle);

    glutSwapBuffers();
} // display

void Graphics::configureAmbientLight(){
    // -- Ambient light
    Color ambient  = Color::ambient;
    Color diffuse  = Color::diffuse;
    Color specular = Color::specular;

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient.toArray1());
    glLightfv(GL_LIGHT0, GL_POSITION, ambient.toArray2());
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse.toArray1());
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular.toArray1());

    glEnable(GL_LIGHT0);
}

void Graphics::positionObserver(float alpha, float beta, int radi){
    float x, y, z;
    float upx, upy, upz;
    float modul;

    x = (float) radi * cos(alpha * 2 * M_PI / 360.0) * cos(beta * 2 * M_PI / 360.0);
    y = (float) radi * sin(beta * 2 * M_PI / 360.0);
    z = (float) radi * sin(alpha * 2 * M_PI / 360.0) * cos(beta * 2 * M_PI / 360.0);

    if (beta > 0) {
        upx = -x;
        upz = -z;
        upy = (x * x + z * z) / y;
    } else if (beta == 0) {
        upx = 0;
        upy = 1;
        upz = 0;
    } else {
        upx = x;
        upz = z;
        upy = -(x * x + z * z) / y;
    }


    modul = sqrt(upx * upx + upy * upy + upz * upz);

    upx = upx / modul;
    upy = upy / modul;
    upz = upz / modul;

    gluLookAt(x, y, z, 0.0, 0.0, 0.0, upx, upy, upz);
}

void Graphics::keyboard(unsigned char c, int x, int y){
    CellType cellType = PLAYER;

    if (!serial->isConnected()) {
        c = tolower(c); // Prevent upper case

        if (c == 'r') game.resetGame();
        else if (c == 'w') game.moveAgent(cellType, UP);
        else if (c == 's') game.moveAgent(cellType, DOWN);
        else if (c == 'a') game.moveAgent(cellType, LEFT);
        else if (c == 'd') game.moveAgent(cellType, RIGHT);
        else if (c == ' ') game.shoot(cellType);

        else if (c == 'i' && anglebeta <= (90 - 4)) anglebeta = (anglebeta + 3);
        else if (c == 'k' && anglebeta >= (-90 + 4)) anglebeta = anglebeta - 3;
        else if (c == 'j') anglealpha = (anglealpha + 3) % 360;
        else if (c == 'l') anglealpha = (anglealpha - 3 + 360) % 360;

        else if (c == '+' && Agent::agentVelocity > 100) Agent::setVelocity(Agent::agentVelocity - 50);
        else if (c == '-' && Agent::agentVelocity < 500) Agent::setVelocity(Agent::agentVelocity + 50);
        else if (c == 'p') game.pauseGame();

        glutPostRedisplay();
    }
}

void Graphics::special(int key, int x, int y){
    CellType cellType = PLAYER;

    if (!serial->isConnected()) {
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
}

void Graphics::idle(){
    long t = glutGet(GLUT_ELAPSED_TIME);

    if (last_t == 0) {
        last_t = t;
    } else {
        game.integrate(t - last_t);
        last_t = t;
    }
    serialRead();

    glutPostRedisplay();
}

void Graphics::serialRead(){
    int buf_max = 256;
    char buf[buf_max];

    if (serial->serialport_read(buf, buf_max))
        parseData(buf);
}

void Graphics::parseData(char * data){
    printf("%s\n", data);
}

void myDisplay(){ Graphics::getInstance().display(); }

void myKeyboard(unsigned char c, int x, int y){ Graphics::getInstance().keyboard(c, x, y); }

void mySpecial(int key, int x, int y){ Graphics::getInstance().special(key, x, y); }

void myIdle(){ Graphics::getInstance().idle(); }
