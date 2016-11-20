/*
 * Project name: Food collection
 * Version 3
 * Student : Albert Eduard Merino Pulido
 */
#include "drawer.h"
Color::Color(const GLfloat red1, const GLfloat green1, const GLfloat blue1,
  const GLfloat red2, const GLfloat green2, const GLfloat blue2)
    : red1(RGBToGlut(red1)), green1(RGBToGlut(green1)), blue1(RGBToGlut(blue1)),
    red2(RGBToGlut(red2)), green2(RGBToGlut(green2)), blue2(RGBToGlut(blue2)){ }

const Color Color::background = Color(0, 0, 0);
const Color Color::text       = Color(0, 150, 0);
const Color Color::wall       = Color(51, 51, 51, 76);
const Color Color::corridor   = Color(0, 0, 80);
const Color Color::food       = Color(255, 214, 0);
const Color Color::player     = Color(255, 255, 0);
const Color Color::enemy      = Color(255, 0, 0);

GLfloat Color::RGBToGlut(int num){
    return num / 255.0;
}

CellProperties::CellProperties(const char symbol, const Color color)
    : symbol(symbol), color(color){ }

const int Drawer::cellSize = 40;
const GLfloat Drawer::x    = Drawer::cellSize / 2.0;
const GLfloat Drawer::y    = Drawer::x;
const GLfloat Drawer::z    = Drawer::cellSize / 5.0;
const GLdouble Drawer::r   = Drawer::cellSize / 8;

const CellProperties CellProperties::wall     = CellProperties('0', Color::wall);
const CellProperties CellProperties::corridor = CellProperties(' ', Color::corridor);
const CellProperties CellProperties::food     = CellProperties('.', Color::food);
const CellProperties CellProperties::player   = CellProperties('p', Color::player);
const CellProperties CellProperties::enemy    = CellProperties('e', Color::enemy);

// Constructors
Drawer::Drawer(){ }

Drawer& Drawer::getInstance(){
    static Drawer instance;

    return instance;
}

void Drawer::setHeight(int height){
    this->height = height;
}

void Drawer::setWidth(int width){
    this->width = width;
}

void Drawer::draw(CellType cellType, float x, float y, bool print, int transalationX, int transalationY){
    glPushMatrix();
    glTranslatef(-(width - y) * Drawer::cellSize + ((width + 1) * Drawer::cellSize / 2.0 + transalationX),
      (height - x) * Drawer::cellSize - ((height + 1) * Drawer::cellSize / 2.0 + transalationY), 0);
    if (print || (cellType != ENEMY && cellType != PLAYER)) {
        switch (cellType) {
            case WALL:
                drawWall();
                break;
            case CORRIDOR:
                drawCorridor();
                break;
            case FOOD:
                drawFood();
                break;
            case PLAYER:
            case ENEMY:
                drawTank(cellType);
                break;
            default:
                break;
        }
    }
    drawCorridor();
    glPopMatrix();
} // draw

void Drawer::drawWall(){
    CellProperties properties = getProperties(WALL);

    drawCube(properties);
} // drawWall

void Drawer::drawCorridor(){
    CellProperties properties = getProperties(CORRIDOR);
    Color color = properties.color;
    GLfloat x   = Drawer::x;
    GLfloat y   = Drawer::y;
    GLfloat z   = Drawer::z;

    glColor3f(color.red1, color.green1, color.blue1);
    glBegin(GL_QUADS);

    glVertex3f(x, y, -z);
    glVertex3f(-x, y, -z);
    glVertex3f(-x, -y, -z);
    glVertex3f(x, -y, -z);


    glEnd();
} // drawCorridor

void Drawer::drawFood(){
    CellProperties properties = getProperties(FOOD);
    Color color = properties.color;
    GLdouble r  = Drawer::r;

    glColor3f(color.red1, color.green1, color.blue1);
    GLUquadric * quad = gluNewQuadric();

    gluSphere(quad, r, 10, 5);

    glEnd();
    gluDeleteQuadric(quad);
} // drawFood

void Drawer::drawTank(CellType cellType){
    CellProperties properties = getProperties(cellType);

    drawFood();
}

void Drawer::drawCube(CellProperties properties){
    Color color = properties.color;
    GLfloat x   = Drawer::x;
    GLfloat y   = Drawer::y;
    GLfloat z   = Drawer::z;

    glColor3f(color.red1, color.green1, color.blue1);
    glBegin(GL_QUADS);
    // FRONT
    glVertex3f(x, y, z);
    glVertex3f(-x, y, z);
    glVertex3f(-x, -y, z);
    glVertex3f(x, -y, z);

    // BACK
    glVertex3f(x, -y, -z);
    glVertex3f(-x, -y, -z);
    glVertex3f(-x, y, -z);
    glVertex3f(x, y, -z);

    // RIGHT
    glColor3f(color.red2, color.green2, color.blue2);
    glVertex3f(x, -y, z);
    glVertex3f(x, -y, -z);
    glVertex3f(x, y, -z);
    glVertex3f(x, y, z);

    // LEFT
    glVertex3f(-x, y, z);
    glVertex3f(-x, y, -z);
    glVertex3f(-x, -y, -z);
    glVertex3f(-x, -y, z);

    // UP
    glVertex3f(x, y, -z);
    glVertex3f(-x, y, -z);
    glVertex3f(-x, y, z);
    glVertex3f(x, y, z);

    // DOWN
    glVertex3f(x, -y, z);
    glVertex3f(-x, -y, z);
    glVertex3f(-x, -y, -z);
    glVertex3f(x, -y, -z);

    glEnd();
} // drawCube

CellProperties Drawer::getProperties(CellType cellType){
    switch (cellType) {
        case WALL:
            return CellProperties::wall;

        case CORRIDOR:
            return CellProperties::corridor;

        case FOOD:
            return CellProperties::food;

        case PLAYER:
            return CellProperties::player;

        case ENEMY:
            return CellProperties::enemy;
    }
    return CellProperties::wall;
}

void Drawer::printScore(int playerScore, int enemyScore){
    ostringstream playerLabel;
    ostringstream enemyLabel;

    playerLabel << "Player: " << playerScore;
    enemyLabel << "Enemy: " << enemyScore;

    printText(width - 0.5, height - 0.5, playerLabel.str());
    printText(width - 0.5, height - 2, enemyLabel.str());
}

void Drawer::printLevel(int level){
    ostringstream levelLabel;

    levelLabel << "Level: " << level;

    printText(width * 0.35 - width, height - 1.5, levelLabel.str());
}

void Drawer::printText(float x, float y, string text){
    Color color   = Color::text;
    GLfloat scale = 0.005 * Drawer::cellSize - 0.05;

    glPushMatrix();
    glTranslatef(-x * Drawer::cellSize / 2.0, y * Drawer::cellSize / 1.5, 0);
    glColor3f(color.red1, color.green1, color.blue1);
    glScalef(scale, scale, 0);
    for (unsigned int i = 0; i < text.size(); i++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
    }
    glPopMatrix();
}
