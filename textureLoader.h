/*
 * Project name: Food collection
 * Version 4
 * Student : Albert Eduard Merino Pulido
 */
#ifndef texture_loader_h
#define texture_loader_h
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "jpeglib.h"
#include "enums.h"

using namespace std;

class TextureLoader {
public:
    // Constructor
    TextureLoader();
    // Methods
    static void loadTextures();
private:
    static void loadTexture(const char *, int);
    static void readJPEG(const char *, unsigned char **, int *, int *);
};
#endif // ifndef texture_loader_h
