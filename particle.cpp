/*
 * Project name: Food collection
 * Version 3
 * Student : Albert Eduard Merino Pulido
 */
#include "particle.h"

Translation::Translation()
    :  x(0), y(0), vx(0), vy(0){ }

Translation::Translation(float x, float y, float vx, float vy)
    :  x(x), y(y), vx(vx), vy(vy){ }

Particle::Particle(){
    state = QUIET;
}

void Particle::init_rotation(float rotation, int duration){
    vr = rotation / duration;
    this->rotation = 0;
    state = ROTATE;
    time_remaining = duration;
}

void Particle::init_movement(Translation t, int duration){
    translation    = Translation(0, 0, t.x / duration, t.y / duration);
    state          = MOVE;
    time_remaining = duration;
}

bool Particle::integrate(long t){
    if (state == MOVE) {
        return integrate_move(t);
    } else if (state == ROTATE) {
        return integrate_rotate(t);
    }
    return false;
}

bool Particle::integrate_move(long t){
    if (t < time_remaining) {
        translation.x  += translation.vx * t;
        translation.y  += translation.vy * t;
        time_remaining -= t;
    } else if (t >= time_remaining) {
        translation.x += translation.vx * time_remaining;
        translation.y += translation.vy * time_remaining;
        state          = QUIET;
        return true;
    }
    return false;
}

bool Particle::integrate_rotate(long t){
    if (t < time_remaining) {
        rotation       += vr * t;
        time_remaining -= t;
    } else if (t >= time_remaining) {
        rotation += vr * time_remaining;
        state     = QUIET;
        return true;
    }
    return false;
}

Translation Particle::getTranslation(){ return translation; }

float Particle::getRotation(){ return rotation; }

State Particle::getState(){ return state; }
