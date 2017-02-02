/*
 * Project name: Food collection
 * Version 4
 * Student : Albert Eduard Merino Pulido
 */
#include "expectimaxAgent.h"

const int ExpectimaxAgent::c1 = 1000;
const int ExpectimaxAgent::c2 = 1;

ExpectimaxAgent::ExpectimaxAgent() : Strategy(){ }

ExpectimaxAgent::ExpectimaxAgent(Map * gameState, CellType agent, int depth)
    : Strategy(gameState, agent), depth(depth){
    best  = INT_MIN;
    alarm = false;
    bestDirections = vector<Direction>();
}

Direction ExpectimaxAgent::getAction(){
    return expectimaxDecision();
}

float ExpectimaxAgent::maxValue(Map gameState, CellType agent, int depth){
    if (terminalTest(gameState, depth))
        return utility(gameState);

    vector<Direction> legalActions = getLegalActions(gameState.getPosition(agent));
    float v = INT_MIN;
    for (unsigned int i = 0; i < legalActions.size(); i++) {
        v = max(v, minValue(result(gameState, agent, legalActions[i]), agent2, depth));
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
        v    = maxValue(result(gameState, agent, legalActions[i]), agent1, depth - 1);
        all += v;
    }
    return all / numOptions;
}

Direction ExpectimaxAgent::expectimaxDecision(){
    float v = INT_MIN;

    vector<Direction> legalActions = getLegalActions(gameState->getPosition(agent1));
    vector<Direction> actions;
    float u;
    if (alarm) {
        bestDirections = blindSearchGraph(*gameState, gameState->getPosition(agent1));
        alarm = false;
        best  = 0;
    }

    for (unsigned int i = 0; i < legalActions.size(); i++) {
        u = minValue(result(*gameState, agent1, legalActions[i]), agent2, depth);
        if (!bestDirections.empty() && legalActions[i] == bestDirections.back()) {
            u *= 2;
            bestDirections.pop_back();
        }
        // std::cout << "u: " << u << '\n';
        if (u == v) {
            actions.push_back(legalActions[i]);
        } else if (u > v) {
            v = u;
            actions.clear();
            actions.push_back(legalActions[i]);
        }
    }

    if (best < v) {
        best = v;
    } else if (v != INT_MIN && v < best - (10 * c1) && bestDirections.empty()) {
        best  = v;
        alarm = true;
    }

    return randomChoice(actions);
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
    float staticScore    = currentGameState.getScore(agent1);
    float mapScore       = 0.0;
    Cell * enemyPosition = currentGameState.getPosition(agent1);
    int d = closestFoodDistance(currentGameState, enemyPosition);

    mapScore += (d == 0.0) ? 50 : 1.0 / (d * d);

    if (agent1 == ENEMY && !currentGameState.isInInitialPosition(agent2)) {
        d = getDistance(currentGameState, enemyPosition, currentGameState.getPosition(agent2));
        if (d <= 1.0) mapScore += 70;
    }
    return c1 * staticScore + c2 * mapScore;
} // evaluationFunction
