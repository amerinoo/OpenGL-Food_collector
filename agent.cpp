/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#include "agent.h"
using namespace std;

const int Agent::initX = 1;
const int Agent::initY = 1;

const int Agent::duration = 250;

// Constructors
Agent::Agent(){ }

Agent::Agent(Cell * cell){
    initPosition = cell;
    state        = QUIET;
    points       = 0;
}

// Getters


int Agent::getPoints(){ return points; }

State Agent::getState(){ return state; }

Direction Agent::getDirection(){ return direction; }

void Agent::setPosition(Cell * cell){
    cell->setCellType(getType());
    position = cell;
}

void Agent::goInitPosition(){
    setPosition(initPosition);
    direction = NONE;
}

void Agent::initMovement(Direction direction, int duration){
    float widthTranslation  = 0;
    float heightTranslation = 0;

    if (direction == UP) heightTranslation = -Cell::cellSize;
    else if (direction == DOWN) heightTranslation = Cell::cellSize;
    else if (direction == LEFT) widthTranslation = -Cell::cellSize;
    else if (direction == RIGHT) widthTranslation = Cell::cellSize;


    vx = widthTranslation / duration;
    vy = heightTranslation / duration;
    transalationX  = 0;
    transalationY  = 0;
    state          = MOVE;
    time_remaining = duration;
}

void Agent::integrate(long t){
    if (state == MOVE && t < time_remaining) {
        transalationX  += vx * t;
        transalationY  += vy * t;
        time_remaining -= t;
    } else if (state == MOVE && t >= time_remaining) {
        transalationX += vx * time_remaining;
        transalationY += vy * time_remaining;
        state          = QUIET;

        position = nextPosition;
        position->setCellType(getType());
        move(direction);
    }
}

void Agent::eat(){
    position->eat();
    points += 1;
}

void Agent::move(Direction direction){
    Cell * cell;

    if (direction == UP) cell = position->getUp();
    else if (direction == DOWN) cell = position->getDown();
    else if (direction == LEFT) cell = position->getLeft();
    else if (direction == RIGHT) cell = position->getRight();

    this->direction = direction;
    if (cell->getType() != WALL) {
        this->setX(position->getX());
        this->setY(position->getY());
        position->setCellType(CORRIDOR);
        nextPosition = cell;
        if (nextPosition->getType() == ENEMY || nextPosition->getType() == PLAYER) {
            goInitPosition();
            return;
        }
        if (cell->hasFood()) eat();
        initMovement(direction, Agent::duration);
    }
} // move

void Agent::draw(){
    if (state == MOVE) Cell::draw(transalationX, transalationY);
} // draw
