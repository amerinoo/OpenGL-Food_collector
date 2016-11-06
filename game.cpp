/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#include "game.h"
using namespace std;


// Constructors
Game::Game(){ }

Game::Game(int height, int width){
    this->height = height;
    this->width  = width;
    newGame();
}

// Getters
int Game::getHeight(){ return height; }

int Game::getWidth(){ return width; }

void Game::draw(){
    vector<vector<Cell *> > m = map.getMap();
    for (int i = 0; i < map.getWidth(); i++)
        for (int j = 0; j < map.getHeigth(); j++)
            m[j][i]->draw();

    player.draw();
    enemy.draw();
}

void Game::newGame(){
    newMap();
    player = Player(map.initPlayer());
    enemy  = Enemy(map.initEnemy());
    map.print();
}

void Game::integrate(long t){
    player.integrate(t);
    enemy.integrate(t);
}

void Game::moveAgent(CellType cellType, Direction direction){
    if (cellType == PLAYER) {
        if (player.getDirection() != direction) player.move(direction);
    } else if (cellType == ENEMY) {
        if (enemy.getDirection() != direction) enemy.move(direction);
    }
}

void Game::newMap(){
    map = Map(height, width);
}
