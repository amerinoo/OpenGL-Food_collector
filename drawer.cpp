/*
 * Project name: Food collection
 * Version 4
 * Student : Albert Eduard Merino Pulido
 */
#include "drawer.h"

Color::Color(const GLfloat red1, const GLfloat green1, const GLfloat blue1, const GLfloat alpha1,
  const GLfloat red2, const GLfloat green2, const GLfloat blue2, const GLfloat alpha2)
    : red1(RGBToGlut(red1)), green1(RGBToGlut(green1)), blue1(RGBToGlut(blue1)), alpha1(RGBToGlut(alpha1)),
    red2(RGBToGlut(red2)), green2(RGBToGlut(green2)), blue2(RGBToGlut(blue2)), alpha2(RGBToGlut(alpha2)){ }

const Color Color::background = Color(64, 64, 64);
const Color Color::text       = Color(0, 150, 0);
const Color Color::wall       = Color(82, 82, 203, 1, 113, 64, 15);
const Color Color::corridor   = Color(0, 0, 80);
const Color Color::food       = Color(0, 255, 230);
const Color Color::player     = Color(255, 255, 0);
const Color Color::enemy      = Color(255, 0, 0);
const Color Color::tank       = Color(153, 153, 153, 1, 51, 51, 51);
const Color Color::bullet     = Color(255, 255, 0);

const Color Color::texture        = Color(255, 255, 255);
const Color Color::light_position = Color(0, 0, 0);
const Color Color::light_ambient  = Color(40, 40, 40);
const Color Color::light_diffuse  = Color(0, 0, 0);
const Color Color::light_specular = Color(0, 0, 0);

const Color Color::light_tank_ambient = Color(20, 20, 20);
const Color Color::light_tank_diffuse = Color(178, 178, 178);

GLfloat Color::RGBToGlut(int num){
    return num / 255.0;
}

GLfloat * Color::toArray1(){
    GLfloat * color = (GLfloat *) malloc(sizeof(GLfloat) * 4);

    color[0] = red1;
    color[1] = green1;
    color[2] = blue1;
    color[3] = alpha1;
    return color;
}

GLfloat * Color::toArray2(){
    GLfloat * color = (GLfloat *) malloc(sizeof(GLfloat) * 4);

    color[0] = red2;
    color[1] = green2;
    color[2] = blue2;
    color[3] = alpha2;
    return color;
}

CellProperties::CellProperties(const char symbol, const Color color)
    : symbol(symbol), color(color){ }

const int Drawer::cellSize          = 40;
const GLfloat Drawer::x             = Drawer::cellSize / 2.0;
const GLfloat Drawer::y             = Drawer::x;
const GLfloat Drawer::z             = Drawer::cellSize / 4.0;
const GLdouble Drawer::foodRadius   = Drawer::cellSize / 6.0;
const GLdouble Drawer::bulletRadius = Drawer::cellSize / 8.0;
const GLint Drawer::slices          = 10;
const GLint Drawer::stacks          = 5;
const GLfloat Drawer::spot_cutoff   = 30.0;
Texture Drawer::textureCorridor     = WATER;

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
    if (print || (cellType != ENEMY && cellType != PLAYER && cellType != BULLET)) {
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
    Color color   = properties.color;
    Color texture = Color::texture;
    GLfloat x     = Drawer::x;
    GLfloat y     = Drawer::y;
    GLfloat z     = Drawer::z;


    glColor3f(color.red1, color.green1, color.blue1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture.toArray1());
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureCorridor);
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(x, y, -z);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-x, y, -z);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-x, -y, -z);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(x, -y, -z);
    glEnd();
    glDisable(GL_TEXTURE_2D);
} // drawCorridor

void Drawer::drawSphere(CellType cellType){
    CellProperties properties = getProperties(cellType);
    Color color = properties.color;
    GLdouble r  = (cellType == BULLET) ? Drawer::bulletRadius : Drawer::foodRadius;

    glColor3f(color.red1, color.green1, color.blue1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color.toArray1());
    glutSolidSphere(r, Drawer::slices, Drawer::stacks);

    glEnd();
} // drawFood

void Drawer::drawTank(CellType cellType, Direction direction, float rotate){
    Color color = getProperties(cellType).color;
    GLfloat x   = Drawer::x / 6.0;
    GLdouble wheelSeparation = 1.8;
    GLdouble s;
    GLdouble h;

    configureLight(cellType, direction);

    glRotatef(90, 1, 0, 0); // Don't touch it.
    glRotatef(direction + rotate, 0, 1, 0);
    glTranslatef(0, 10, -Drawer::cellSize / 2.5);

    s = x / 2.0;
    h = x * 5.0;
    drawCanon(s, h, Color::tank);
    drawHead(Color::tank);

    // Dibuixa cos
    s = x * 2;
    h = s * 1.5;
    glTranslatef(0, -x * 2.5, -s / 1.2);
    drawCanon(s, h, color);

    s = x * 1.5;
    h = s * 5;
    // Dibuixa roda dreta
    glTranslatef(s * wheelSeparation, -s, -s * 3.5);
    drawWheel(s, h, color);

    // Dibuixa roda esquerra
    glTranslatef(-s * wheelSeparation * 2, 0, -s * 5);
    drawWheel(s, h, color);
} // drawTank

void Drawer::drawCanon(GLdouble s, GLdouble h, Color color){
    GLUquadric * quad = gluNewQuadric();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color.toArray1());
    gluCylinder(quad, s, s, h, Drawer::slices, Drawer::stacks);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color.toArray2());
    gluSphere(quad, s, Drawer::slices, Drawer::stacks);
    glTranslatef(0, 0, h);
    gluSphere(quad, s, Drawer::slices, Drawer::stacks);

    gluDeleteQuadric(quad);
}

void Drawer::drawWheel(GLdouble s, GLdouble h, Color color){
    GLUquadric * quad = gluNewQuadric();

    drawCanon(s, h, color);
    glTranslatef(0, 0, -h * 1.16);
    GLfloat white[] = { 255.0, 255.0, 255.0, 1 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
    gluSphere(quad, s / 4.0, Drawer::slices, Drawer::stacks);
    glTranslatef(0, 0, h * 1.16);

    gluDeleteQuadric(quad);
}

void Drawer::drawHead(Color color){
    GLfloat x = Drawer::x / 6.0;
    GLfloat y = x;
    GLfloat z = x;

    glColor3f(color.red2, color.green2, color.blue2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color.toArray2());
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
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color.toArray2());
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
    Color texture    = Color::texture;

    glColor3f(color.red1, color.green1, color.blue1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, texture.toArray1());

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, WOOD);
    glBegin(GL_QUADS);
    // FRONT
    glNormal3f(0, 0, 1);
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
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color.toArray2());
    // BACK
    glNormal3f(0, 0, -1);
    glVertex3f(x, -y, -z);
    glVertex3f(-x, -y, -z);
    glVertex3f(-x, y, -z);
    glVertex3f(x, y, -z);

    // RIGHT
    glNormal3f(1, 0, 0);
    glVertex3f(x, -y, z);
    glVertex3f(x, -y, -z);
    glVertex3f(x, y, -z);
    glVertex3f(x, y, z);

    // LEFT
    glNormal3f(-1, 0, 0);
    glVertex3f(-x, y, z);
    glVertex3f(-x, y, -z);
    glVertex3f(-x, -y, -z);
    glVertex3f(-x, -y, z);

    // UP
    glNormal3f(0, 1, 0);
    glVertex3f(x, y, -z);
    glVertex3f(-x, y, -z);
    glVertex3f(-x, y, z);
    glVertex3f(x, y, z);

    // DOWN
    glNormal3f(0, -1, 0);
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
    ostringstream label;

    label << "Level: " << level;
    printText(width * 0.08, height * 0.95, label.str(), GLUT_BITMAP_HELVETICA_12);
}

void Drawer::printVelocity(int velocity){
    ostringstream label;

    label << "Velocity: " << velocity;
    printText(width * 0.8, height * 0.95, label.str(), GLUT_BITMAP_HELVETICA_12);
}

void Drawer::printFood(int food){
    ostringstream label;

    label << food;
    printText(width * 0.48, height * 0.03, label.str(), GLUT_BITMAP_HELVETICA_12);
}

void Drawer::printArduino(bool isConnected){
    ostringstream label;

    label << isConnected;
    printText(width * 0.95, height * 0.95, label.str(), GLUT_BITMAP_HELVETICA_12);
}

void Drawer::printText(float x, float y, string text, void * font){
    glDisable(GL_LIGHTING);
    Color color = Color::text;

    glRasterPos2f(x, y);
    glColor3f(color.red1, color.green1, color.blue1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color.toArray2());
    for (unsigned int i = 0; i < text.size(); i++) {
        glutBitmapCharacter(font, text[i]);
    }
    glEnable(GL_LIGHTING);
}

void Drawer::configureLight(CellType cellType, Direction direction){
    Color position = Color::light_position;
    Color ambient  = Color::light_tank_ambient;
    Color diffuse  = Color::light_tank_diffuse;
    GLenum light   = (cellType == PLAYER) ? GL_LIGHT1 : GL_LIGHT2;

    glLightfv(light, GL_POSITION, position.toArray1());
    glLightfv(light, GL_AMBIENT, ambient.toArray1());
    glLightf(light, GL_CONSTANT_ATTENUATION, 1.0);
    glLightf(light, GL_LINEAR_ATTENUATION, 0.0);
    glLightf(light, GL_QUADRATIC_ATTENUATION, 0.0);
    glLightfv(light, GL_DIFFUSE, diffuse.toArray1());
    glLightfv(light, GL_SPOT_DIRECTION, getSpotDirection(direction));
    glLightf(light, GL_SPOT_CUTOFF, Drawer::spot_cutoff);
    glLightf(light, GL_SPOT_EXPONENT, 0);

    glEnable(light);
} // configureLight

GLfloat * Drawer::getSpotDirection(Direction direction){
    GLfloat * spot_dir = (GLfloat *) malloc(sizeof(GLfloat) * 3);
    GLfloat dirHor     = 0;
    GLfloat dirVer     = 0;

    if (direction == RIGHT) dirHor = 1;
    else if (direction == LEFT) dirHor = -1;
    else if (direction == UP) dirVer = 1;
    else if (direction == DOWN) dirVer = -1;

    spot_dir[0] = dirHor; // 1 right -1 left
    spot_dir[1] = dirVer; // 1 up -1 down
    spot_dir[2] = 0;

    return spot_dir;
}
