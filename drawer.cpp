/*
 * Project name: Food collection
 * Version 4
 * Student : Albert Eduard Merino Pulido
 */
#include "drawer.h"
Color::Color(const GLfloat red1, const GLfloat green1, const GLfloat blue1,
  const GLfloat red2, const GLfloat green2, const GLfloat blue2)
    : red1(RGBToGlut(red1)), green1(RGBToGlut(green1)), blue1(RGBToGlut(blue1)),
    red2(RGBToGlut(red2)), green2(RGBToGlut(green2)), blue2(RGBToGlut(blue2)){ }

const Color Color::background = Color(64, 64, 64);
const Color Color::text       = Color(0, 150, 0);
const Color Color::wall       = Color(82, 82, 203, 51, 51, 153);
const Color Color::corridor   = Color(0, 0, 80);
const Color Color::food       = Color(0, 255, 230);
const Color Color::player     = Color(255, 255, 0);
const Color Color::enemy      = Color(255, 0, 0);
const Color Color::tank       = Color(153, 153, 153, 51, 51, 51);
const Color Color::bullet     = Color(255, 255, 0);

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
const GLint Drawer::slices = 10;
const GLint Drawer::stacks = 5;

const CellProperties CellProperties::wall     = CellProperties('0', Color::wall);
const CellProperties CellProperties::corridor = CellProperties(' ', Color::corridor);
const CellProperties CellProperties::food     = CellProperties('.', Color::food);
const CellProperties CellProperties::player   = CellProperties('p', Color::player);
const CellProperties CellProperties::enemy    = CellProperties('e', Color::enemy);
const CellProperties CellProperties::bullet   = CellProperties('o', Color::bullet);

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

void Drawer::draw(CellType cellType, float x, float y, bool print,
  Direction direction, int rotation, int transalationX, int transalationY){
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
                break;
            case FOOD:
                drawSphere(cellType);
                break;
            case PLAYER:
            case ENEMY:
                drawTank(cellType, direction, rotation);
                break;
            case BULLET:
                drawSphere(cellType);
                break;
            default:
                break;
        }
    }
    if (!print && cellType != WALL) drawCorridor();
    glPopMatrix();
} // draw

void Drawer::drawWall(){
    CellProperties properties = getProperties(WALL);

    drawCube(properties.color);
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

void Drawer::drawSphere(CellType cellType){
    CellProperties properties = getProperties(cellType);
    Color color = properties.color;
    GLdouble r  = Drawer::r;

    glColor3f(color.red1, color.green1, color.blue1);
    GLUquadric * quad = gluNewQuadric();

    gluSphere(quad, r, Drawer::slices, Drawer::stacks);

    gluDeleteQuadric(quad);
    glEnd();
} // drawFood

void Drawer::drawTank(CellType cellType, Direction direction, float rotate){
    Color color = getProperties(cellType).color;
    GLfloat x   = Drawer::x / 6.0;
    GLdouble wheelSeparation = 1.8;
    GLdouble s;
    GLdouble h;

    glRotatef(90, 1, 0, 0); // Don't touch it.
    glRotatef(direction + rotate, 0, 1, 0);
    glTranslatef(0, 10, -Drawer::cellSize / 2.5);

    s = x / 2.0;
    h = x * 5.0;
    drawCylinder(s, h, Color::tank);
    drawHead(Color::tank);

    // Dibuixa cos
    s = x * 2;
    h = s * 1.5;
    glTranslatef(0, -x * 2.5, -s / 1.2);
    drawCylinder(s, h, color);

    // Dibuixa roda dreta
    s = x * 1.5;
    h = s * 5;
    glTranslatef(s * wheelSeparation, -s, -s * 3.5);
    drawCylinder(s, h, color);

    // Dibuixa roda esquerra
    glTranslatef(-s * wheelSeparation * 2, 0, -s * 5);
    drawCylinder(s, h, color);
} // drawTank

void Drawer::drawCylinder(GLdouble s, GLdouble h, Color color){
    GLUquadric * quad = gluNewQuadric();

    glColor3f(color.red1, color.green1, color.blue1);
    gluCylinder(quad, s, s, h, Drawer::slices, Drawer::stacks);
    glColor3f(color.red2, color.green2, color.blue2);
    gluSphere(quad, s, Drawer::slices, Drawer::stacks);
    glTranslatef(0, 0, h);
    gluSphere(quad, s, Drawer::slices, Drawer::stacks);

    gluDeleteQuadric(quad);
    glEnd();
}

void Drawer::drawHead(Color color){
    GLfloat x = Drawer::x / 6.0;
    GLfloat y = x;
    GLfloat z = x;

    glColor3f(color.red2, color.green2, color.blue2);
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
} // drawHead

void Drawer::drawCube(Color color){
    GLfloat x        = Drawer::x;
    GLfloat y        = Drawer::y;
    GLfloat z        = Drawer::z;
    float pixelError = 0.5;

    glColor3f(color.red1, color.green1, color.blue1);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBegin(GL_QUADS);
    // FRONT
    glTexCoord2f(0.0, 0.0);
    glVertex3f(x, y, z + pixelError);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-x, y, z + pixelError);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-x, -y, z + pixelError);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(x, -y, z + pixelError);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glColor3f(color.red2, color.green2, color.blue2);
    // BACK
    glVertex3f(x, -y, -z);
    glVertex3f(-x, -y, -z);
    glVertex3f(-x, y, -z);
    glVertex3f(x, y, -z);

    // RIGHT
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

        case BULLET:
            return CellProperties::bullet;

        case PLAYER:
            return CellProperties::player;

        case ENEMY:
            return CellProperties::enemy;

        default: break;
    }
    return CellProperties::wall;
}

void Drawer::printTitle(const char * title){
    printText(0, 0, "", GLUT_BITMAP_8_BY_13);
    printText(width * 0.39, height * 0.96, title, GLUT_BITMAP_HELVETICA_18);
    printText(width * 0.44, height * 0.935, "Albert Merino", GLUT_BITMAP_HELVETICA_12);
}

void Drawer::printScore(int playerScore, int enemyScore){
    ostringstream playerLabel;
    ostringstream enemyLabel;

    playerLabel << "Player: " << playerScore;
    enemyLabel << "Enemy: " << enemyScore;
    printText(width * 0.08, height * 0.03, playerLabel.str(), GLUT_BITMAP_HELVETICA_12);
    printText(width * 0.83, height * 0.03, enemyLabel.str(), GLUT_BITMAP_HELVETICA_12);
}

void Drawer::printLevel(int level){
    ostringstream levelLabel;

    levelLabel << "Level: " << level;
    printText(width * 0.08, height * 0.95, levelLabel.str(), GLUT_BITMAP_HELVETICA_12);
}

void Drawer::printVelocity(int velocity){
    ostringstream velocityLabel;

    velocityLabel << "Velocity: " << velocity;
    printText(width * 0.8, height * 0.95, velocityLabel.str(), GLUT_BITMAP_HELVETICA_12);
}

void Drawer::printFood(int food){
    ostringstream foodLabel;

    foodLabel << food;
    printText(width * 0.48, height * 0.03, foodLabel.str(), GLUT_BITMAP_HELVETICA_12);
}

void Drawer::printText(float x, float y, string text, void * font){
    Color color = Color::text;

    glRasterPos2f(x, y);
    glColor3f(color.red1, color.green1, color.blue1);
    for (unsigned int i = 0; i < text.size(); i++) {
        glutBitmapCharacter(font, text[i]);
    }
}
