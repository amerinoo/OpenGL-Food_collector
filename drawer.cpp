/*
 * Project name: Food collection
 * Version 3
 * Student : Albert Eduard Merino Pulido
 */
#include "drawer.h"
Color::Color(const GLfloat red, const GLfloat green, const GLfloat blue)
    : red(RGBToGlut(red)), green(RGBToGlut(green)),
    blue(RGBToGlut(blue)){ }

const Color Color::background = Color(0, 0, 0);
const Color Color::text       = Color(0, 150, 0);
const Color Color::wall       = Color(0, 57, 255);
const Color Color::corridor   = Color::background;
const Color Color::food       = Color(224, 128, 234);
const Color Color::player     = Color(255, 255, 0);
const Color Color::enemy      = Color(255, 0, 0);

GLfloat Color::RGBToGlut(int num){
    return num / 255.0;
}

CellProperties::CellProperties(const char symbol, const Color color,
  const int padding, const ShapeType shape, const int radius)
    : symbol(symbol), color(color), padding(padding), shape(shape),
    radius(radius){ }

const int Drawer::cellSize = 40;

const CellProperties CellProperties::wall = CellProperties('0',
  Color::wall, Drawer::cellSize * 0.0, SQUARE, 0);
const CellProperties CellProperties::corridor = CellProperties(' ',
  Color::corridor, Drawer::cellSize * 0.0, SQUARE, 0);
const CellProperties CellProperties::food = CellProperties('.',
  Color::food, Drawer::cellSize * 0.43, SQUARE, Drawer::cellSize * 0.15);
const CellProperties CellProperties::player = CellProperties('p',
  Color::player, Drawer::cellSize * 0.25, CIRCLE, Drawer::cellSize * 0.3);
const CellProperties CellProperties::enemy = CellProperties('e',
  Color::enemy, Drawer::cellSize * 0.25, CIRCLE, Drawer::cellSize * 0.3);

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
      (height - x) * Drawer::cellSize - ((height + 1) * Drawer::cellSize / 2.0 + transalationY),
      0);
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
                drawFood();
                break;
            case ENEMY:
                drawFood();
                break;
            default:
                break;
        }
    }
    drawCorridor();
    glPopMatrix();
} // draw

void Drawer::drawWall(){
    GLint x = Drawer::cellSize / 2;
    GLint y = x;
    GLint z = Drawer::cellSize / 5;

    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_QUADS);
    // FRONT
    glVertex3f(x, y, z);
    glVertex3i(-x, y, z);
    glVertex3i(-x, -y, z);
    glVertex3i(x, -y, z);

    // BACK
    glVertex3i(x, -y, -z);
    glVertex3i(-x, -y, -z);
    glVertex3i(-x, y, -z);
    glVertex3i(x, y, -z);

    // RIGHT
    glColor3f(0.3, 0.0, 0);
    glVertex3i(x, -y, z);
    glVertex3i(x, -y, -z);
    glVertex3i(x, y, -z);
    glVertex3i(x, y, z);

    // LEFT
    glVertex3i(-x, y, z);
    glVertex3i(-x, y, -z);
    glVertex3i(-x, -y, -z);
    glVertex3i(-x, -y, z);

    // UP
    glVertex3i(x, y, -z);
    glVertex3i(-x, y, -z);
    glVertex3i(-x, y, z);
    glVertex3i(x, y, z);

    // DOWN
    glVertex3i(x, -y, z);
    glVertex3i(-x, -y, z);
    glVertex3i(-x, -y, -z);
    glVertex3i(x, -y, -z);

    glEnd();
} // drawWall

void Drawer::drawCorridor(){
    GLint x = Drawer::cellSize / 2;
    GLint y = x;
    GLint z = Drawer::cellSize / 5;

    glColor3f(0.0, 0.0, 0.6);
    glBegin(GL_QUADS);

    glVertex3i(x, y, -z);
    glVertex3i(-x, y, -z);
    glVertex3i(-x, -y, -z);
    glVertex3i(x, -y, -z);


    glEnd();
} // drawCorridor

void Drawer::drawFood(){
    GLint r = Drawer::cellSize / 8;

    glColor3f(1.0, 0.84, 0.0);
    GLUquadric * quad = gluNewQuadric();

    gluSphere(quad, r, 50, 20);

    glEnd();
    gluDeleteQuadric(quad);
} // drawCorridor

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
    glColor3f(color.red, color.green, color.blue);
    glScalef(scale, scale, 0);
    for (unsigned int i = 0; i < text.size(); i++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
    }
    glPopMatrix();
}
