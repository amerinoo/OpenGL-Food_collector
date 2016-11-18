/*
 * Project name: Food collection
 * Version 3
 * Student : Albert Eduard Merino Pulido
 */
#ifndef particle_h
#define particle_h
#include <GL/glut.h>
#include "enums.h"

class Particle {
    float vx, vy; // -- Velocity vector
    float transalationX, transalationY;
    State state;

    long time_remaining;

public:
    Particle();
    void init_movement(float, float, int);
    bool integrate(long);
    float getTranslationX();
    float getTranslationY();
    State getState();
};
#endif
