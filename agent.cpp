/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#include "agent.h"
using namespace std;

const int Agent::duration = 250;

// Constructors
Agent::Agent(){ }

Agent::Agent(CellType cellType, Cell * cell){
    setCellType(cellType);
    initPosition = cell;
    state        = QUIET;
    score        = 0;
    goInitPosition();
}

// Getters


int Agent::getScore(){ return score; }

State Agent::getState(){ return state; }

Cell * Agent::getCurrentPosition(){ return currentPosition; }

Direction Agent::getDirection(){ return direction; }

void Agent::setPosition(Cell * cell){
    cell->setCellType(getType());
    currentPosition = cell;
    this->setX(currentPosition->getX());
    this->setY(currentPosition->getY());
}

void Agent::setDirection(Direction direction){
    this->direction = direction;
}

void Agent::setNextDirection(Direction nextDirection){
    this->nextDirection = nextDirection;
}

void Agent::goInitPosition(){
    setPosition(initPosition);
    direction     = NONE;
    nextDirection = NONE;
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

bool Agent::integrate(long t){
    if (state == MOVE && t < time_remaining) {
        transalationX  += vx * t;
        transalationY  += vy * t;
        time_remaining -= t;
    } else if (state == MOVE && t >= time_remaining) {
        transalationX += vx * time_remaining;
        transalationY += vy * time_remaining;
        state          = QUIET;

        currentPosition = nextPosition;
        setPosition(currentPosition);
        return true;
    }
    return false;
}

void Agent::eat(){
    currentPosition->eat();
    score += 1;
}

void Agent::move(){
    Cell * cell = NULL;

    if (direction == UP) cell = currentPosition->getUp();
    else if (direction == DOWN) cell = currentPosition->getDown();
    else if (direction == LEFT) cell = currentPosition->getLeft();
    else if (direction == RIGHT) cell = currentPosition->getRight();

    if (cell != NULL && cell->getType() != WALL) {
        currentPosition->setCellType(CORRIDOR);
        nextPosition = cell; /* message *//* message */
        if (nextPosition->getType() == ENEMY || nextPosition->getType() == PLAYER) {
            goInitPosition();
            return;
        }
        if (cell->hasFood()) eat();
        initMovement(direction, Agent::duration);
    }
} // move

void Agent::tryNextDirection(){
    Cell * cell = NULL;

    if (nextDirection == UP) cell = currentPosition->getUp();
    else if (nextDirection == DOWN) cell = currentPosition->getDown();
    else if (nextDirection == LEFT) cell = currentPosition->getLeft();
    else if (nextDirection == RIGHT) cell = currentPosition->getRight();
    if ((cell != NULL && cell->getType() != WALL) || direction == NONE) {
        direction     = nextDirection;
        nextDirection = NONE;
    }
}

void Agent::draw(){
    if (state == MOVE) Cell::draw(transalationX, transalationY);
} // draw
