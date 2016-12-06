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

    player->draw();
    enemy->draw();
    Drawer& drawer = Drawer::getInstance();
    drawer.printScore(player->getScore(), enemy->getScore());
    drawer.printLevel(level);
}

void Game::resetGame(){
    level = 0;
    pause = false;
    newGame();
}

void Game::newGame(){
    newMap();
    level += 1;
    player = new Agent(PLAYER, map.initPlayer(), new Strategy(map));
    enemy  = new Agent(ENEMY, map.initEnemy(), new ReflexAgent(map));
    player->setAgent(enemy);
    enemy->setAgent(player);
    map.print();
}

void Game::pauseGame(){
    pause = !pause;
}

void Game::integrate(long t){
    if (!pause) {
        integrate(player, t);
        integrate(enemy, t);
    }
}

void Game::integrate(Agent * agent, long t){
    if (agent->integrate(t) || agent->isQuiet()) {
        if (map.hasFood()) {
            agent->setPosition(agent->getNextPosition());
            Direction d = agent->getStrategy()->getAction(agent->getCurrentPosition());
            agent->setNextDirection(d);
            agent->tryNextDirection();
            if (agent->move()) map.eat();
        } else { finish(); }
    }
}

void Game::finish(){
    if (playerWin()) newGame();
    else resetGame();
}

bool Game::playerWin(){ return player->getScore() > enemy->getScore(); }

void Game::moveAgent(CellType cellType, Direction direction){
    if (cellType == PLAYER) {
        if (player->isQuiet()) player->setDirection(direction);
        else player->setNextDirection(direction);
    }
}

void Game::shoot(CellType cellType){
    if (cellType == PLAYER) {
        player->shoot();
    }
}

void Game::newMap(){
    map = Map(height, width);
}
