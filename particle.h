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
    float vx, vy, vr; // -- Velocity vector
    float transalationX, transalationY, rotation;
    State state;

    long time_remaining;

public:
    Particle();
    void init_rotation(float, int);
    void init_movement(float, float, int);
    bool integrate(long);
    bool integrate_move(long);
    bool integrate_rotate(long);
    float getTranslationX();
    float getTranslationY();
    float getRotation();
    State getState();
};
#endif
