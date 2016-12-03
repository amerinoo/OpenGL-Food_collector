/*
 * Project name: Food collection
 * Version 3
 * Student : Albert Eduard Merino Pulido
 */
#include "particle.h"

Particle::Particle(){
    state = QUIET;
}

void Particle::init_rotation(float rotation, int duration){
    vr = rotation / duration;
    this->rotation = 0;
    state = ROTATE;
    time_remaining = duration;
}

void Particle::init_movement(float widthTranslation, float heightTranslation, int duration){
    vx = widthTranslation / duration;
    vy = heightTranslation / duration;
    transalationX  = 0;
    transalationY  = 0;
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
        transalationX  += vx * t;
        transalationY  += vy * t;
        time_remaining -= t;
    } else if (t >= time_remaining) {
        transalationX += vx * time_remaining;
        transalationY += vy * time_remaining;
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

float Particle::getTranslationX(){ return transalationX; }

float Particle::getTranslationY(){ return transalationY; }

float Particle::getRotation(){ return rotation; }

State Particle::getState(){ return state; }
