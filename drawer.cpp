#include "drawer.h"
Color::Color(const GLfloat red, const GLfloat green, const GLfloat blue)
    : red(RGBToGlut(red)), green(RGBToGlut(green)),
    blue(RGBToGlut(blue)){ }

const Color Color::background = Color(0, 0, 0);
const Color Color::wall       = Color(0, 57, 255);
const Color Color::corridor   = Color(0, 0, 0);
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
const CellProperties CellProperties::corridor = CellProperties('.',
  Color::corridor, Drawer::cellSize * 0.0, SQUARE, 0);
const CellProperties CellProperties::food = CellProperties('*',
  Color::food, Drawer::cellSize * 0.43, SQUARE, Drawer::cellSize * 0.15);
const CellProperties CellProperties::player = CellProperties('p',
  Color::player, Drawer::cellSize * 0.25, CIRCLE, Drawer::cellSize * 0.3);
const CellProperties CellProperties::enemy = CellProperties('e',
  Color::enemy, Drawer::cellSize * 0.25, CIRCLE, Drawer::cellSize * 0.3);

Drawer::Drawer(){ }

void Drawer::draw(CellType cellType, float x, float y, bool print){
    if (print || (cellType != ENEMY && cellType != PLAYER)) draw(cellType, x, y, 0, 0);
}

void Drawer::draw(CellType cellType, float x, float y, int transalationX, int transalationY){
    Color color     = getProperties(cellType).color;
    ShapeType shape = getProperties(cellType).shape;

    glColor3f(color.red, color.green, color.blue);
    if (shape == CIRCLE) {
        drawCircle(cellType, x, y, transalationX, transalationY);
    } else if (shape == SQUARE) {
        drawSquare(cellType, x, y, transalationX, transalationY);
    }
} // draw

void Drawer::drawCircle(CellType cellType, float x, float y, int transalationX, int transalationY){
    int radius      = getProperties(cellType).radius;
    int rep         = 50;
    GLfloat twicePi = 2.0f * M_PI;

    float x1 = ((y + 1) * Drawer::cellSize) - Drawer::cellSize / 2.0 + transalationX;
    float y1 = ((x + 1) * Drawer::cellSize) - Drawer::cellSize / 2.0 + transalationY;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x1, y1);
    for (int i = 0; i < rep; i++) {
        glVertex2f(
          x1 + (radius * cos(i * twicePi / rep)),
          y1 + (radius * sin(i * twicePi / rep))
        );
    }
    glEnd();
}

void Drawer::drawSquare(CellType cellType, float x, float y, int transalationX, int transalationY){
    int padding = getProperties(cellType).padding;

    glBegin(GL_QUADS);

    glVertex2i(y * Drawer::cellSize + padding + transalationX,
      x * Drawer::cellSize + padding + transalationY);
    glVertex2i((y + 1) * Drawer::cellSize - padding + transalationX,
      x * Drawer::cellSize + padding + transalationY);
    glVertex2i((y + 1) * Drawer::cellSize - padding + transalationX,
      (x + 1) * Drawer::cellSize - padding + transalationY);
    glVertex2i(y * Drawer::cellSize + padding + transalationX,
      (x + 1) * Drawer::cellSize - padding + transalationY);

    glEnd();
}

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
