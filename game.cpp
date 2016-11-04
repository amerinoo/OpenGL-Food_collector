/*
 * Project name: Food collection
 * Version 1
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#include "game.h"
using namespace std;


    
// Constructors
Game::Game(){ }
Game::Game(int heigth, int width){ 
    newMap(heigth,width);
    player = Player();
    player.setPosition(map.getMap()[1][1]);
    enemy = Enemy();
    enemy.setPosition(map.getMap()[1][width-2]);
}


void Game::draw(){
    vector<vector<Cell *> > m = map.getMap();
    for (int i = 0; i < map.getWidth(); i++) 
        for (int j = 0; j < map.getHeigth(); j++)
            m[j][i]->draw();
    
    player.draw();
    enemy.draw();
}

void Game::newMap(){
    newMap(map.getHeigth(), map.getWidth());
}
void Game::newMap(int heigth, int width){
    map = Map(heigth, width);
    map.print();
}

Map Game::getMap(){return map;}