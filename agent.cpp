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

Direction Agent::getDirection(){ return direction; }

void Agent::setPosition(Cell * cell){
    cell->setCellType(getType());
    position = cell;
    this->setX(position->getX());
    this->setY(position->getY());
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

        position = nextPosition;
        setPosition(position);
        return true;
    }
    return false;
}

void Agent::eat(){
    position->eat();
    score += 1;
}

void Agent::move(){
    Cell * cell = NULL;

    if (direction == UP) cell = position->getUp();
    else if (direction == DOWN) cell = position->getDown();
    else if (direction == LEFT) cell = position->getLeft();
    else if (direction == RIGHT) cell = position->getRight();

    if (cell != NULL && cell->getType() != WALL) {
        position->setCellType(CORRIDOR);
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

    if (nextDirection == UP) cell = position->getUp();
    else if (nextDirection == DOWN) cell = position->getDown();
    else if (nextDirection == LEFT) cell = position->getLeft();
    else if (nextDirection == RIGHT) cell = position->getRight();
    if ((cell != NULL && cell->getType() != WALL) || direction == NONE) {
        direction     = nextDirection;
        nextDirection = NONE;
    }
}

void Agent::draw(){
    if (state == MOVE) Cell::draw(transalationX, transalationY);
} // draw
