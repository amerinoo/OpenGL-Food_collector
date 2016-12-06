/*
 * Project name: Food collection
 * Version 3
 * Student : Albert Eduard Merino Pulido
 */
#include "agent.h"
using namespace std;

int Agent::duration = 200;

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

bool Agent::isQuiet(){ return getState() == QUIET; }

bool Agent::isMove(){ return getState() == MOVE; }

bool Agent::isRotate(){ return getState() == ROTATE; }

Cell * Agent::getCurrentPosition(){ return currentPosition; }

Cell * Agent::getNextPosition(){ return nextPosition; }

Direction Agent::getDirection(){ return currentDirection; }

void Agent::setPosition(Cell * cell){
    cell->setCellType(cellType);
    currentPosition = cell;
}

void Agent::setDirection(Direction currentDirection){
    if (currentDirection != NONE && this->currentDirection != NONE) {
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
    lastDirection    = DOWN;
    currentDirection = NONE;
    nextDirection    = NONE;
}

void Agent::eat(){
    score += 1;
}

bool Agent::move(){
    Cell * cell = NULL;
    bool eat    = false;
    Translation translation;

    if (currentDirection != NONE) {
        cell        = getNextPosition(currentDirection);
        translation = getTranslation(currentDirection);
        if (needRotate) {
            rotate();
        } else if (!cell->isWall()) {
            nextPosition = cell;
            particle.init_movement(translation, Agent::duration);
            if (isCrash()) {
                agent->getCurrentPosition()->setCellType(CORRIDOR);
                agent->goInitPosition();
            } else if (cell->hasFood()) {
                this->eat();
                eat = true;
            }
        }
    }
    return eat;
} // move

Translation Agent::getTranslation(Direction direction){
    Translation translation;

    if (direction == UP) translation.y = -Drawer::cellSize;
    else if (direction == DOWN) translation.y = Drawer::cellSize;
    else if (direction == LEFT) translation.x = -Drawer::cellSize;
    else if (direction == RIGHT) translation.x = Drawer::cellSize;
    return translation;
}

bool Agent::isCrash(){
    return (cellType == ENEMY) ?
           nextPosition == agent->getNextPosition() ||
           currentPosition == agent->getNextPosition() ||
           currentPosition == agent->getCurrentPosition() ||
           nextPosition == agent->getCurrentPosition() : false;
}

void Agent::rotate(){
    float r = currentDirection - lastDirection;

    if (r != 0) {
        if (r > 180) r -= 360;
        else if (r < -180) r += 360;
        particle.init_rotation(r, Agent::duration);
    }
    needRotate = false;
}

void Agent::shoot(){
    std::cout << "SHOOT " << currentDirection << std::endl;
}

void Agent::tryNextDirection(){
    Cell * cell = getNextPosition(nextDirection);

    if ((cell != NULL && !cell->isWall()) || currentDirection == NONE) {
        setDirection(nextDirection);
        nextDirection = NONE;
    }
}

Cell * Agent::getNextPosition(Direction direction){
    Cell * cell = NULL;

    if (direction == UP) cell = currentPosition->getUp();
    else if (direction == DOWN) cell = currentPosition->getDown();
    else if (direction == LEFT) cell = currentPosition->getLeft();
    else if (direction == RIGHT) cell = currentPosition->getRight();
    return cell;
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
    Drawer& drawer      = Drawer::getInstance();
    Direction direction = (currentDirection != NONE) ? currentDirection : lastDirection;

    if (isMove()) {
        drawer.draw(cellType, currentPosition->getX(), currentPosition->getY(),
          true, direction, 0, particle.getTranslation().x, particle.getTranslation().y);
    } else if (isRotate()) {
        drawer.draw(cellType, currentPosition->getX(), currentPosition->getY(),
          true, lastDirection, particle.getRotation());
    } else {
        drawer.draw(cellType, currentPosition->getX(), currentPosition->getY(),
          true, direction);
    }
}
