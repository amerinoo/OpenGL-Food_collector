/*
 * Project name: Food collection
 * Version 3
 * Student : Albert Eduard Merino Pulido
 */
#include "game.h"
using namespace std;


// Constructors
Game::Game(){ }

Game::Game(int height, int width){
    this->height = height;
    this->width  = width;
    resetGame();
}

// Getters
int Game::getHeight(){ return height; }

int Game::getWidth(){ return width; }

void Game::draw(){
    vector<vector<Cell *> > m = map.getMap();
    for (int i = 0; i < map.getHeigth(); i++)
        for (int j = 0; j < map.getWidth(); j++)
            m[i][j]->draw();

    player.draw();
    enemy.draw();
    Drawer& drawer = Drawer::getInstance();
    drawer.printScore(player.getScore(), enemy.getScore());
    drawer.printLevel(level);
}

void Game::resetGame(){
    level = 0;
    newGame();
}

void Game::newGame(){
    newMap();
    level += 1;
    player = Agent(PLAYER, map.initPlayer(), new Strategy(map));
    enemy  = Agent(ENEMY, map.initEnemy(), new ReflexAgent(map));
    player.setAgent(&enemy);
    enemy.setAgent(&player);
    map.print();
}

void Game::integrate(long t){
    if (map.hasFood()) {
        integrate(&player, t);
        integrate(&enemy, t);
    } else {
        if (player.getScore() > enemy.getScore()) {
            newGame();
        } else { resetGame(); }
    }
}

void Game::integrate(Agent * agent, long t){
    if (agent->integrate(t) || agent->getState() == QUIET) {
        agent->setPosition(agent->getNextPosition());
        Direction d = agent->getStrategy()->getAction(agent->getCurrentPosition());
        agent->setNextDirection(d);
        agent->tryNextDirection();
        if (agent->move()) map.eat();
    }
}

void Game::moveAgent(CellType cellType, Direction direction){
    if (cellType == PLAYER) {
        if (player.getState() == QUIET) {
            player.setDirection(direction);
            if (player.move()) map.eat();
        } else {
            player.setNextDirection(direction);
        }
    } else if (cellType == ENEMY) {
        enemy.setNextDirection(direction);
    }
}

void Game::newMap(){
    map = Map(height, width);
}
