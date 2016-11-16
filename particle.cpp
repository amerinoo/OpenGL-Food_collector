#include "particle.h"
// -----------------------------------------------

Particle::Particle(){
    state = QUIET;
}

// -----------------------------------------------

void Particle::set_position(int x, int y){
    this->x = x;
    this->y = y;
}

// -----------------------------------------------

void Particle::init_movement(int destination_x, int destination_y, int duration){
    vx = (destination_x - x) / duration;
    vy = (destination_y - y) / duration;

    state = MOVE;
    time_remaining = duration;
}

// -----------------------------------------------

bool Particle::integrate(long t){
    if (state == MOVE && t < time_remaining) {
        x = x + vx * t;
        y = y + vy * t;
        time_remaining -= t;
    } else if (state == MOVE && t >= time_remaining) {
        x     = x + vx * time_remaining;
        y     = y + vy * time_remaining;
        state = QUIET;
        return true;
    }
    return false;
}

// -----------------------------------------------

void Particle::draw(){
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex2i(x - 6, y - 6);
    glVertex2i(x + 6, y - 6);
    glVertex2i(x + 6, y + 6);
    glVertex2i(x - 6, y + 6);
    glEnd();
}
