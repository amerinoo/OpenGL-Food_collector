/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#include "strategy.h"
Strategy::Strategy(){ }

Strategy::Strategy(Map map) : map(map){ }

Direction Strategy::getAction(Agent agent){
    Cell * c = agent.getCurrentPosition();

    vector<Direction> legalActions = getLegalActions(c);
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

vector<Direction> Strategy::getLegalActions(Cell * c){
    vector<Direction> legalActions;

    if (c->getUp()->getType() != WALL)
        legalActions.push_back(UP);
    if (c->getDown()->getType() != WALL)
        legalActions.push_back(DOWN);
    if (c->getLeft()->getType() != WALL)
        legalActions.push_back(LEFT);
    if (c->getRight()->getType() != WALL)
        legalActions.push_back(RIGHT);

    return legalActions;
}

float Strategy::evaluationFunction(Cell * currentPosition, Direction direction){
    float totalScore    = 0.0;
    Cell * nextPosition = getNextState(currentPosition, direction);

    vector<Cell *> food = map.getFood();
    for (unsigned int i = 0; i < food.size(); i++) {
        int d = manhattanDistance(nextPosition, food[i]);
        if (d == 0.0) {
            totalScore += 100;
        } else {
            totalScore += 1.0 / (d * d);
        }
    }
    return totalScore;
} // evaluationFunction

Cell * Strategy::getNextState(Cell * cell, Direction direction){
    if (direction == UP) return cell->getUp();
    else if (direction == DOWN) return cell->getDown();
    else if (direction == LEFT) return cell->getLeft();
    else return cell->getRight();
}

double Strategy::manhattanDistance(Cell * c1, Cell * c2){
    return abs(c2->getX() - c1->getX()) + abs(c2->getY() - c1->getY());
}
