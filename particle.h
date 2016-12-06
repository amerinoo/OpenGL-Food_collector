/*
 * Project name: Food collection
 * Version 3
 * Student : Albert Eduard Merino Pulido
 */
#ifndef particle_h
#define particle_h
#include <GL/glut.h>
#include "enums.h"

typedef struct Translation{

    float x;
    float y;
    float vx;
    float vy;
    Translation();
    Translation(float, float, float=0, float=0);
} Translation;

class Particle {
    float vr; // -- Velocity vector
    float rotation;
    Translation translation;
    State state;

    long time_remaining;

public:
    Particle();
    void init_rotation(float, int);
    void init_movement(Translation, int);
    bool integrate(long);
    bool integrate_move(long);
    bool integrate_rotate(long);
    Translation getTranslation();
    float getRotation();
    State getState();
};
#endif
