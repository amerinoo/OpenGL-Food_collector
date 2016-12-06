/*
 * Project name: Food collection
 * Version 3
 * Student : Albert Eduard Merino Pulido
 */
#include "agent.h"
using namespace std;

int Agent::agentVelocity  = 200;
int Agent::rotateVelocity = Agent::agentVelocity / 1.5;
int Agent::bulletVelocity = Agent::agentVelocity / 1.8;

void Agent::setVelocity(int v){
    Agent::agentVelocity  = v;
    Agent::rotateVelocity = Agent::agentVelocity / 1.5;
    Agent::bulletVelocity = Agent::agentVelocity / 1.8;
}

Bullet::Bullet(){ enable = true; }

Bullet::Bullet(Cell * position, Direction direction)
    : position(position), direction(direction){ Bullet(); }

// Constructors
Agent::Agent(){ }

Agent::Agent(CellType cellType, Cell * initPosition, Strategy * strategy)
    : cellType(cellType), initPosition(initPosition){
    this->strategy = strategy;
    map   = strategy->getMap();
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
    map->eat();
}

void Agent::move(){
    if (currentDirection != NONE) {
        if (needRotate) rotate();
        else move(getNextPosition(currentDirection, currentPosition)); }
} // move

void Agent::move(Cell * cell){
    if (!cell->isWall()) {
        nextPosition = cell;
        particle.init_movement(getTranslation(currentDirection), Agent::agentVelocity);
        if (isCrash()) crash();
        else if (cell->hasFood()) eat();
    }
}

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

void Agent::crash(){
    agent->getCurrentPosition()->setCellType(CORRIDOR);
    agent->goInitPosition();
}

void Agent::rotate(){
    float r = currentDirection - lastDirection;

    if (r != 0) {
        if (r > 180) r -= 360;
        else if (r < -180) r += 360;
        particle.init_rotation(r, Agent::rotateVelocity);
    }
    needRotate = false;
}

void Agent::shoot(){
    if (canShoot()) {
        bullet = Bullet(currentPosition, currentDirection);
        bullet.particle.init_movement(getTranslation(bullet.direction), Agent::bulletVelocity);
        bullet.enable = false;
    }
}

bool Agent::canShoot(){
    return bullet.enable &&
           !isRotate() &&
           currentDirection != NONE;
}

void Agent::tryNextDirection(){
    Cell * cell = getNextPosition(nextDirection, currentPosition);

    if ((cell != NULL && !cell->isWall()) || currentDirection == NONE) {
        setDirection(nextDirection);
        nextDirection = NONE;
    }
}

Cell * Agent::getNextPosition(Direction direction, Cell * position){
    Cell * cell = NULL;

    if (direction == UP) cell = position->getUp();
    else if (direction == DOWN) cell = position->getDown();
    else if (direction == LEFT) cell = position->getLeft();
    else if (direction == RIGHT) cell = position->getRight();
    return cell;
}

bool Agent::integrate(long t){
    if (bullet.particle.integrate(t)) {
        moveBullet();
    }
    if (particle.integrate(t)) {
        currentPosition->setCellType(CORRIDOR);
        currentPosition = nextPosition;
        currentPosition->setCellType(cellType);
        return true;
    }
    return false;
}

void Agent::moveBullet(){
    bullet.position = getNextPosition(bullet.direction, bullet.position);
    if (bullet.position->isWall()) bullet.enable = true;
    else if (isCrashBullet()) crashBullet();
    else bullet.particle.init_movement(getTranslation(bullet.direction), Agent::bulletVelocity);
}

bool Agent::isCrashBullet(){
    return (cellType == PLAYER) ?
           bullet.position == agent->getCurrentPosition() : false;
}

void Agent::crashBullet(){ crash(); bullet.enable = true; }

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
    if (!bullet.enable) {
        drawer.draw(BULLET, bullet.position->getX(), bullet.position->getY(),
          true, bullet.direction, 0, bullet.particle.getTranslation().x, bullet.particle.getTranslation().y);
    }
}
