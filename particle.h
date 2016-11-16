/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#ifndef particle_h
#define particle_h
#include "cell.h"
class Particle {
    float x, y;   // -- Current position
    float vx, vy; // -- Velocity vector
    State state;

    long time_remaining;

public:

    Particle();
    void set_position(int x, int y);
    void init_movement(int destination_x, int destination_y, int duration);
    bool integrate(long t);
    void draw();
};
#endif
