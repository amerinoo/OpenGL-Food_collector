/*
 * Project name: Food collection
 * Version 4
 * Student : Albert Eduard Merino Pulido
 */
#include "strategy.h"
Strategy::Strategy(){ }

Strategy::Strategy(Map * gameState) : gameState(gameState){ }

Map * Strategy::getGameState(){ return gameState; }

Direction Strategy::getAction(){ return NONE; }

vector<Direction> Strategy::getLegalActions(Cell * c){
    return gameState->getLegalActions(c);
}

float Strategy::getDistance(Cell * c1, Cell * c2){
    return manhattanDistance(c1, c2);
}

float Strategy::manhattanDistance(Cell * c1, Cell * c2){
    return abs(c2->getX() - c1->getX()) + abs(c2->getY() - c1->getY());
}
