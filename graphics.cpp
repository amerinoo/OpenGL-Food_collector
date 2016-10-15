#include <GL/glut.h>
#include "graphics.h"

Graphics::Graphics(){ }

Graphics::Graphics(Map m){
    init(m);
}

Graphics::Graphics(char * fname){
    map = getMapFromFile(fname);
    init(map);
}

void Graphics::init(Map m){
    map     = m;
    COLUMNS = m.getMap()[0].size();
    ROWS    = m.getMap().size();
    HEIGHT  = ROWS * 20;
    WIDTH   = COLUMNS * 20;
}

int Graphics::getHeight(){ return HEIGHT; }

int Graphics::getWidth(){ return WIDTH; }

void Graphics::display(){
    vector<vector<Cell *> > m = map.getMap();
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    int a = WIDTH / COLUMNS;
    int b = HEIGHT / ROWS;
    for (int i = 0; i < COLUMNS; i++) {
        for (int j = 0; j < ROWS; j++) {
            if (m[j][i]->getSymbol() == '0') {
                glBegin(GL_QUADS);
                glColor3f(0, 0, 1);

                glVertex2i(i * a, j * b);             // esquerra dalt
                glVertex2i((i + 1) * a, j * b);       // dreta dalt
                glVertex2i((i + 1) * a, (j + 1) * b); // dreta baix
                glVertex2i(i * a, (j + 1) * b);       // esquerra baix

                glEnd();
            }
        }
    }

    glutSwapBuffers();
} // display

Map Graphics::getMapFromFile(char * fname){
    vector<vector<Cell *> > m;
    string s = "";
    string saux;
    ifstream in(fname); // Open for reading
    int width;
    while (getline(in, saux)) {
        if (s == "") width = saux.size();
        s += saux;
    }
    int heigth = s.size() / width;
    int w      = 0;
    for (int i = 0; i < heigth; i++) {
        vector<Cell *> aux;
        for (int j = 0; j < width; j++) {
            if (s[w] == '0') {
                aux.push_back(new Wall(i, j));
            } else if (s[w] == '.') {
                aux.push_back(new Corridor(i, j));
            }
            w++;
        }
        m.push_back(aux);
    }
    return Map(m);
}
