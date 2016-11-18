/*
 * Project name: Food collection
 * Version 3
 * Student : Albert Eduard Merino Pulido
 */
#include "reflexAgent.h"
ReflexAgent::ReflexAgent() : Strategy(){ }

ReflexAgent::ReflexAgent(Map map) : Strategy(map){ }

Direction ReflexAgent::getAction(Cell * c){
    vector<Direction> legalActions = map.getLegalActions(c);
    vector<float> scores;

    for (unsigned int i = 0; i < legalActions.size(); i++) {
        scores.push_back(evaluationFunction(c, legalActions[i]));
    }
    float bestScore = -99999999999999999;
    for (unsigned int i = 0; i < scores.size(); i++) {
        if (scores[i] > bestScore) {
            bestScore = scores[i];
        }
    }
    vector<int> bestIndices;
    for (unsigned int i = 0; i < scores.size(); i++) {
        if (scores[i] == bestScore) {
            bestIndices.push_back(i);
        }
    }
    random_shuffle(bestIndices.begin(), bestIndices.end());
    return legalActions[bestIndices[0]];
} // getAction

float ReflexAgent::evaluationFunction(Cell * currentPosition, Direction direction){
    float totalScore    = 0.0;
    Cell * nextPosition = getNextState(currentPosition, direction);

    vector<Cell *> food = map.getFood();
    for (unsigned int i = 0; i < food.size(); i++) {
        int d = manhattanDistance(nextPosition, food[i]);
        totalScore += (d == 0.0) ? 100 : 1.0 / (d * d);
    }
    return totalScore;
} // evaluationFunction

Cell * ReflexAgent::getNextState(Cell * cell, Direction direction){
    if (direction == UP) return cell->getUp();
    else if (direction == DOWN) return cell->getDown();
    else if (direction == LEFT) return cell->getLeft();
    else return cell->getRight();
}

double ReflexAgent::manhattanDistance(Cell * c1, Cell * c2){
    return abs(c2->getX() - c1->getX()) + abs(c2->getY() - c1->getY());
}
