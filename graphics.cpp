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
    game.drawText(windowTitle, serial->isConnected());

    glutSwapBuffers();
} // display

void Graphics::configureAmbientLight(){
    // -- Ambient light
    Color position = Color::light_position;
    Color ambient  = Color::light_ambient;
    Color diffuse  = Color::light_diffuse;
    Color specular = Color::light_specular;

    glLightfv(GL_LIGHT0, GL_POSITION, position.toArray1());
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient.toArray1());
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
    makeAction(c);
}

void Graphics::special(int key, int x, int y){
    makeAction(key);
}

void Graphics::makeAction(unsigned char c, CellType cellType){
    c = tolower(c); // Prevent upper case

    if (c == K_R) game.resetGame();
    else if (c == K_W) game.moveAgent(cellType, UP);
    else if (c == K_S) game.moveAgent(cellType, DOWN);
    else if (c == K_A) game.moveAgent(cellType, LEFT);
    else if (c == K_D) game.moveAgent(cellType, RIGHT);
    else if (c == K_SPACE) game.shoot(cellType);

    else if (c == K_I && anglebeta <= (90 - 4)) anglebeta = (anglebeta + 3);
    else if (c == K_K && anglebeta >= (-90 + 4)) anglebeta = anglebeta - 3;
    else if (c == K_J) anglealpha = (anglealpha + 3) % 360;
    else if (c == K_L) anglealpha = (anglealpha - 3 + 360) % 360;

    else if (c == K_PLUS && Agent::agentVelocity > 100) Agent::setVelocity(Agent::agentVelocity - 50);
    else if (c == K_MINUS && Agent::agentVelocity < 500) Agent::setVelocity(Agent::agentVelocity + 50);
    else if (c == K_P) game.pauseGame();

    glutPostRedisplay();
}

void Graphics::makeAction(int key, CellType cellType){
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
    serialRead();

    glutPostRedisplay();
}

void Graphics::serialRead(){
    int buf_max = 256;
    char buf[buf_max];

    if (serial->serialport_read(buf, buf_max)) parseData(buf);
}

void Graphics::parseData(char * d){
    Sensor sensor;
    string data(d);
    Json::Value root;
    Json::Reader reader;
    bool success = reader.parse(d, root);

    if (success) {
        sensor.horz = root.get(string(1, JOYSTICK_HORZ), "-1").asInt();
        sensor.vert = root.get(string(1, JOYSTICK_VERT), "-1").asInt();
        sensor.sel  = root.get(string(1, JOYSTICK_SEL), "-1").asInt();

        joystick(sensor);
    }
} // parseData

void Graphics::joystick(Sensor sensor){
    unsigned char direction;

    if (sensor.horz > sensor.vert) {
        if (sensor.horz >= 100) direction = K_D;
        else direction = K_A;
    } else {
        if (sensor.vert >= 100) direction = K_W;
        else direction = K_S;
    }
    makeAction(direction);
    if (sensor.sel == 0) {
        /* Switch player lights */
    }
}

void myDisplay(){ Graphics::getInstance().display(); }

void myKeyboard(unsigned char c, int x, int y){ Graphics::getInstance().keyboard(c, x, y); }

void mySpecial(int key, int x, int y){ Graphics::getInstance().special(key, x, y); }

void myIdle(){ Graphics::getInstance().idle(); }
