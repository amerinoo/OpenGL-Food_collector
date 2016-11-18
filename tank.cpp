#include <GL/glut.h>
#include <math.h>

#define PI     3.1416

#define WIDTH  600
#define HEIGHT 400

#define ALPHA  240
#define BETA   20


/*--- Global variables that determine the viewpoint location ---*/
int anglealpha = 0;
int anglebeta  = 0;

// -----------------------------------------------
// -----------------------------------------------

void
PositionObserver(float alpha, float beta, int radi);

void
display();
void
keyboard(unsigned char c, int x, int y);

void
body(GLint, GLdouble, GLdouble);
void
wheel(GLint, GLdouble, GLdouble);


// -----------------------------------------------
// -----------------------------------------------

int main(int argc, char * argv[]){
    anglealpha = ALPHA;
    anglebeta  = BETA;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(1100, 500);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("3D Hello World");
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}

// -----------------------------------------------
// -----------------------------------------------

void PositionObserver(float alpha, float beta, int radi){
    float x, y, z;
    float upx, upy, upz;
    float modul;

    x = (float) radi * cos(alpha * 2 * PI / 360.0) * cos(beta * 2 * PI / 360.0);
    y = (float) radi * sin(beta * 2 * PI / 360.0);
    z = (float) radi * sin(alpha * 2 * PI / 360.0) * cos(beta * 2 * PI / 360.0);

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

// -----------------------------------------------
// -----------------------------------------------
void display(){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    PositionObserver(anglealpha, anglebeta, 450);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIDTH * 0.6, WIDTH * 0.6, -HEIGHT * 0.9, HEIGHT * 0.6, 10, 2000);

    glMatrixMode(GL_MODELVIEW);

    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);
    // RED GREEN BLUE
    GLint x = 40;
    GLint y = x;
    GLint z = x;
    GLUquadric * quad = gluNewQuadric();
    glColor3f(0.6, 0.6, 0.6);
    gluCylinder(quad, x / 2, x / 2, x * 5, 50, 20);
    gluSphere(quad, x / 2, 50, 20);
    glTranslatef(0, 0, x * 5);
    gluSphere(quad, x / 2, 50, 20);

    glColor3f(0.2, 0.2, 0.2);
    // glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3i(x, y, z);
    glVertex3i(-x, y, z);
    glVertex3i(-x, -y, z);
    glVertex3i(x, -y, z);
    glEnd();

    // glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
    glVertex3i(x, -y, z);
    glVertex3i(x, -y, -z);
    glVertex3i(x, y, -z);
    glVertex3i(x, y, z);
    glEnd();

    // glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3i(x, -y, -z);
    glVertex3i(-x, -y, -z);
    glVertex3i(-x, y, -z);
    glVertex3i(x, y, -z);
    glEnd();

    // glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3i(-x, y, z);
    glVertex3i(-x, y, -z);
    glVertex3i(-x, -y, -z);
    glVertex3i(-x, -y, z);
    glEnd();

    // glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3i(x, y, -z);
    glVertex3i(-x, y, -z);
    glVertex3i(-x, y, z);
    glVertex3i(x, y, z);
    glEnd();

    // glColor3f(0.75, 0.2, 0.75);
    glBegin(GL_QUADS);
    glVertex3i(x, -y, z);
    glVertex3i(-x, -y, z);
    glVertex3i(-x, -y, -z);
    glVertex3i(x, -y, -z);
    glEnd();

    GLdouble s;
    GLdouble h;
    GLdouble wheelSeparation = 1.8;
    // Dibuixa cos
    s = x * 2;
    h = s * 1.5;
    glTranslatef(0, -x, 0);
    body(x, s, h);

    // Dibuixa roda dreta
    s = x * 1.5;
    h = s * 5;
    glTranslatef(s * wheelSeparation, -s, -s * 4);
    wheel(x, s, h);

    // Dibuixa roda esquerra
    glTranslatef(-s * wheelSeparation * 2, 0, 0);
    wheel(x, s, h);

    glutSwapBuffers();
} // display

void body(GLint x, GLdouble s, GLdouble h){
    GLUquadric * quad = gluNewQuadric();

    glColor3f(0.9, 0.9, 0);
    glTranslatef(0, -80, -s / 1.2);
    gluCylinder(quad, s, s, h, 50, 20);
    gluSphere(quad, s, 50, 20);
    glTranslatef(0, 0, s * 1.5);
    gluSphere(quad, s, 50, 20);

    glEnd();
    gluDeleteQuadric(quad);
}

void wheel(GLint x, GLdouble s, GLdouble h){
    GLUquadric * quad = gluNewQuadric();

    glColor3f(0.9, 0.9, 0);
    gluSphere(quad, s, 50, 20);
    glTranslatef(0, 0, h);
    gluSphere(quad, s, 50, 20);
    glTranslatef(0, 0, -h);
    glColor3f(0, 0.4, 0);
    gluCylinder(quad, s, s, h, 50, 20);

    glEnd();
    gluDeleteQuadric(quad);
}

// -----------------------------------------------
// -----------------------------------------------
void keyboard(unsigned char c, int x, int y){
    if (c == 'w' && anglebeta <= (90 - 4)) {
        anglebeta = (anglebeta + 3);
    } else if (c == 's' && anglebeta >= (-90 + 4)) {
        anglebeta = anglebeta - 3;
    } else if (c == 'a') {
        anglealpha = (anglealpha + 3) % 360;
    } else if (c == 'd') {
        anglealpha = (anglealpha - 3 + 360) % 360;
    } else if (c == 'r') {
        anglealpha = ALPHA;
        anglebeta  = BETA;
    }

    glutPostRedisplay();
}
