#include "particle.h"

Particle::Particle(){
    state = QUIET;
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
    if (state == MOVE && t < time_remaining) {
        transalationX  += vx * t;
        transalationY  += vy * t;
        time_remaining -= t;
    } else if (state == MOVE && t >= time_remaining) {
        transalationX += vx * time_remaining;
        transalationY += vy * time_remaining;
        state          = QUIET;
        return true;
    }
    return false;
}

float Particle::getTranslationX(){ return transalationX; }

float Particle::getTranslationY(){ return transalationY; }

State Particle::getState(){ return state; }
