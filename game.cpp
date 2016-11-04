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
}


void Game::draw(){
    vector<vector<Cell *> > m = map.getMap();
    for (int i = 0; i < map.getWidth(); i++) 
        for (int j = 0; j < map.getHeigth(); j++) 
            m[j][i]->draw(i,j);
}

void Game::newMap(){
    newMap(map.getHeigth(), map.getWidth());
}
void Game::newMap(int heigth, int width){
    map = Map(heigth, width);
    map.print();
}

Map Game::getMap(){return map;}