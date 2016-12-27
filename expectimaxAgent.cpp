/*
 * Project name: Food collection
 * Version 4
 * Student : Albert Eduard Merino Pulido
 */
#include "expectimaxAgent.h"

ExpectimaxAgent::ExpectimaxAgent() : Strategy(){ }

ExpectimaxAgent::ExpectimaxAgent(Map * gameState, int depth) : Strategy(gameState), depth(depth){ }

Direction ExpectimaxAgent::getAction(){
    return expectimaxDecision();
}

float ExpectimaxAgent::maxValue(Map gameState, CellType agent, int depth){
    if (terminalTest(gameState, depth))
        return utility(gameState);

    vector<Direction> legalActions = getLegalActions(gameState.getPosition(agent));
    float v = INT_MIN;
    for (unsigned int i = 0; i < legalActions.size(); i++) {
        v = max(v, minValue(result(gameState, agent, legalActions[i]), PLAYER, depth));
    }
    return v;
}

float ExpectimaxAgent::minValue(Map gameState, CellType agent, int depth){
    if (terminalTest(gameState, depth))
        return utility(gameState);

    float all = 0;
    vector<Direction> legalActions = getLegalActions(gameState.getPosition(agent));
    float numOptions = legalActions.size();
    float v = INT_MAX;
    for (unsigned int i = 0; i < legalActions.size(); i++) {
        v    = maxValue(result(gameState, agent, legalActions[i]), ENEMY, depth - 1);
        all += v;
    }
    return all / numOptions;
}

Direction ExpectimaxAgent::expectimaxDecision(){
    float v = INT_MIN;

    vector<Direction> legalActions = getLegalActions(gameState->getPosition(ENEMY));
    vector<Direction> actions;
    float u;

    for (unsigned int i = 0; i < legalActions.size(); i++) {
        u = minValue(result(*gameState, ENEMY, legalActions[i]), PLAYER, depth);
        if (u == v) {
            actions.push_back(legalActions[i]);
        } else if (u > v) {
            v = u;
            actions.clear();
            actions.push_back(legalActions[i]);
        }
    }
    random_shuffle(actions.begin(), actions.end());
    return actions[0];
} // expectimaxDecision

float ExpectimaxAgent::utility(Map gameState){
    return evaluationFunction(gameState);
}

bool ExpectimaxAgent::terminalTest(Map gameState, int depth){
    return depth == 0 || !gameState.hasFood();
}

Map ExpectimaxAgent::result(Map gameState, CellType agent, Direction action){
    return gameState.generateSuccessor(agent, action);
}

float ExpectimaxAgent::evaluationFunction(Map currentGameState){
    float totalScore     = currentGameState.getScore(ENEMY);
    Cell * enemyPosition = currentGameState.getPosition(ENEMY);
    float d;

    vector<Cell *> food = currentGameState.getFood();
    for (unsigned int i = 0; i < food.size(); i++) {
        d = getDistance(enemyPosition, food[i]);
        totalScore += (d == 0.0) ? 50 : 1.0 / (d * d);
    }

    d = getDistance(enemyPosition, currentGameState.getPosition(PLAYER));
    if (d <= 1.0) {
        totalScore += 300;
    }
    return totalScore;
} // evaluationFunction
