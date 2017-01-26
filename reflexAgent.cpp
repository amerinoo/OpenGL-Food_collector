/*
 * Project name: Food collection
 * Version 4
 * Student : Albert Eduard Merino Pulido
 */
#include "reflexAgent.h"
ReflexAgent::ReflexAgent() : Strategy(){ }

ReflexAgent::ReflexAgent(Map * gameState, CellType agent) : Strategy(gameState, agent){ }

Direction ReflexAgent::getAction(){
    Cell * c = gameState->getPosition(agent1);

    vector<Direction> legalActions = getLegalActions(c);
    vector<float> scores;

    for (unsigned int i = 0; i < legalActions.size(); i++) {
        scores.push_back(evaluationFunction(*gameState, legalActions[i]));
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

float ReflexAgent::evaluationFunction(Map currentGameState, Direction direction){
    float totalScore       = 0.0;
    Cell * currentPosition = currentGameState.getPosition(agent1);
    Cell * nextPosition    = currentGameState.getNextState(currentPosition, direction);

    vector<Cell *> food = gameState->getFood();
    for (unsigned int i = 0; i < food.size(); i++) {
        int d = getDistance(currentGameState, nextPosition, food[i]);
        totalScore += (d == 0.0) ? 50 : 1.0 / (d * d);
    }
    return totalScore;
} // evaluationFunction
