/*
 * Project name: Food collection
 * Version 3
 * Student : Albert Eduard Merino Pulido
 */
#include "agent.h"
using namespace std;

int Agent::duration = 250;

// Constructors
Agent::Agent(){ }

Agent::Agent(CellType cellType, Cell * initPosition, Strategy * strategy)
    : cellType(cellType), initPosition(initPosition){
    this->strategy = strategy;
    score = 0;
    goInitPosition();
}

// Getters
Strategy * Agent::getStrategy(){ return strategy; }

int Agent::getScore(){ return score; }

State Agent::getState(){ return particle.getState(); }

Cell * Agent::getCurrentPosition(){ return currentPosition; }

Cell * Agent::getNextPosition(){ return nextPosition; }

Direction Agent::getDirection(){ return currentDirection; }

void Agent::setPosition(Cell * cell){
    cell->setCellType(cellType);
    currentPosition = cell;
}

void Agent::setDirection(Direction currentDirection){
    if (currentDirection != NONE) {
        lastDirection = this->currentDirection;
    }
    needRotate = this->currentDirection != currentDirection;
    this->currentDirection = currentDirection;
}

void Agent::setNextDirection(Direction nextDirection){
    if (nextDirection != NONE) this->nextDirection = nextDirection;
}

void Agent::setAgent(Agent * agent){ this->agent = agent; }

void Agent::goInitPosition(){
    setPosition(initPosition);
    nextPosition     = initPosition;
    lastDirection    = NONE;
    currentDirection = NONE;
    nextDirection    = NONE;
}

void Agent::eat(){
    score += 1;
}

bool Agent::move(){
    Cell * cell = NULL;
    bool eat    = false;
    float widthTranslation  = 0;
    float heightTranslation = 0;

    if (currentDirection != NONE) {
        if (currentDirection == UP) {
            cell = currentPosition->getUp();
            heightTranslation = -Drawer::cellSize;
        } else if (currentDirection == DOWN) {
            cell = currentPosition->getDown();
            heightTranslation = Drawer::cellSize;
        } else if (currentDirection == LEFT) {
            cell = currentPosition->getLeft();
            widthTranslation = -Drawer::cellSize;
        }    else if (currentDirection == RIGHT) {
            cell = currentPosition->getRight();
            widthTranslation = Drawer::cellSize;
        }

        if (needRotate) {
            float r = currentDirection - lastDirection;
            if (r > 180) r -= 360;
            else if (r < -180) r += 360;
            particle.init_rotation(r, Agent::duration);
            needRotate = false;
        } else if (cell->getType() != WALL) {
            if (cell->getType() == CORRIDOR) {
                nextPosition = cell;
            } else if (cell->getType() == FOOD) {
                nextPosition = cell;
                this->eat();
                eat = true;
            } else if (cell->getType() == ENEMY) {
                currentPosition->setCellType(CORRIDOR);
                goInitPosition();
            } else if (cell->getType() == PLAYER) {
                nextPosition = cell;
                agent->getCurrentPosition()->setCellType(CORRIDOR);
                agent->goInitPosition();
            }

            particle.init_movement(widthTranslation, heightTranslation, Agent::duration);
        }
    }
    return eat;
} // move

void Agent::tryNextDirection(){
    Cell * cell = NULL;

    if (nextDirection == UP) cell = currentPosition->getUp();
    else if (nextDirection == DOWN) cell = currentPosition->getDown();
    else if (nextDirection == LEFT) cell = currentPosition->getLeft();
    else if (nextDirection == RIGHT) cell = currentPosition->getRight();
    if ((cell != NULL && cell->getType() != WALL) || currentDirection == NONE) {
        setDirection(nextDirection);
        nextDirection = NONE;
    }
}

bool Agent::integrate(long t){
    if (particle.integrate(t)) {
        currentPosition->setCellType(CORRIDOR);
        currentPosition = nextPosition;
        currentPosition->setCellType(cellType);
        return true;
    }
    return false;
}

void Agent::draw(){
    Direction direction;

    if (currentDirection != NONE) {
        direction = currentDirection;
    } else {
        direction = lastDirection;
    }
    Drawer& drawer = Drawer::getInstance();

    if (particle.getState() == MOVE) {
        drawer.draw(cellType, currentPosition->getX(), currentPosition->getY(),
          true, direction, 0, particle.getTranslationX(), particle.getTranslationY());
    } else if (particle.getState() == ROTATE) {
        drawer.draw(cellType, currentPosition->getX(), currentPosition->getY(),
          true, lastDirection, particle.getRotation());
    } else {
        drawer.draw(cellType, currentPosition->getX(), currentPosition->getY(),
          true, direction);
    }
}
