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

Agent::Agent(CellType cellType, Cell * initPosition, Strategy * strategy)
    : cellType(cellType), initPosition(initPosition){
    this->strategy = strategy;
    state        = QUIET;
    score        = 0;
    nextPosition = initPosition;
    goInitPosition();
}

// Getters
Strategy * Agent::getStrategy(){ return strategy; }

int Agent::getScore(){ return score; }

State Agent::getState(){ return state; }

Cell * Agent::getCurrentPosition(){ return currentPosition; }

Cell * Agent::getNextPosition(){ return nextPosition; }

Direction Agent::getDirection(){ return currentDirection; }

void Agent::setPosition(Cell * cell){
    cell->setCellType(cellType);
    currentPosition = cell;
}

void Agent::setDirection(Direction currentDirection){
    this->currentDirection = currentDirection;
}

void Agent::setNextDirection(Direction nextDirection){
    if (nextDirection != NONE) this->nextDirection = nextDirection;
}

void Agent::goInitPosition(){
    setPosition(initPosition);
    currentDirection = NONE;
    nextDirection    = NONE;
}

void Agent::initMovement(Direction currentDirection, int duration){
    float widthTranslation  = 0;
    float heightTranslation = 0;

    if (currentDirection == UP) heightTranslation = -Cell::cellSize;
    else if (currentDirection == DOWN) heightTranslation = Cell::cellSize;
    else if (currentDirection == LEFT) widthTranslation = -Cell::cellSize;
    else if (currentDirection == RIGHT) widthTranslation = Cell::cellSize;


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

    if (currentDirection == UP) cell = currentPosition->getUp();
    else if (currentDirection == DOWN) cell = currentPosition->getDown();
    else if (currentDirection == LEFT) cell = currentPosition->getLeft();
    else if (currentDirection == RIGHT) cell = currentPosition->getRight();

    if (cell != NULL && cell->getType() != WALL) {
        currentPosition->setCellType(CORRIDOR);
        nextPosition = cell;
        if (nextPosition->getType() == ENEMY || nextPosition->getType() == PLAYER) {
            goInitPosition();
            return;
        }
        if (cell->hasFood()) eat();
        initMovement(currentDirection, Agent::duration);
    }
} // move

void Agent::tryNextDirection(){
    Cell * cell = NULL;

    if (nextDirection == UP) cell = currentPosition->getUp();
    else if (nextDirection == DOWN) cell = currentPosition->getDown();
    else if (nextDirection == LEFT) cell = currentPosition->getLeft();
    else if (nextDirection == RIGHT) cell = currentPosition->getRight();
    if ((cell != NULL && cell->getType() != WALL) || currentDirection == NONE) {
        currentDirection = nextDirection;
        nextDirection    = NONE;
    }
}

void Agent::draw(){
    if (state == MOVE) {
        currentPosition->setCellType(cellType);
        currentPosition->draw(transalationX, transalationY);
        currentPosition->setCellType(CORRIDOR);
    }
} // draw
