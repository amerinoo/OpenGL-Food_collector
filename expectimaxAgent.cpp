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
    // for (unsigned int i = 0; i < actions.size(); i++) {
    //     switch (actions[i]) {
    //         case UP:
    //             std::cout << "UP, ";
    //             break;
    //
    //         case DOWN:
    //             std::cout << "DOWN, ";
    //             break;
    //
    //         case LEFT:
    //             std::cout << "LEFT, ";
    //             break;
    //
    //         case RIGHT:
    //             std::cout << "RIGHT, ";
    //             break;
    //
    //         case NONE:
    //             std::cout << "NONE, ";
    //             break;
    //     }
    // }
    // std::cout << std::endl;
    random_shuffle(actions.begin(), actions.end());
    // for (unsigned int i = 0; i < actions.size(); i++) {
    //     switch (actions[i]) {
    //         case UP:
    //             std::cout << "UP, ";
    //             break;
    //
    //         case DOWN:
    //             std::cout << "DOWN, ";
    //             break;
    //
    //         case LEFT:
    //             std::cout << "LEFT, ";
    //             break;
    //
    //         case RIGHT:
    //             std::cout << "RIGHT, ";
    //             break;
    //
    //         case NONE:
    //             std::cout << "NONE, ";
    //             break;
    //     }
    // }
    // std::cout << std::endl;
    // std::cout << std::endl;
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
    float staticScore    = currentGameState.getScore(ENEMY);
    float mapScore       = 0.0;
    Cell * enemyPosition = currentGameState.getPosition(ENEMY);
    float d;

    vector<Cell *> food = currentGameState.getCandidateFood();
    for (unsigned int i = 0; i < food.size(); i++) {
        d         = getDistance(enemyPosition, food[i]);
        mapScore += (d == 0.0) ? 50 : 1.0 / (d * d);
    }
    if (!currentGameState.isInInitialPosition(PLAYER)) {
        d = getDistance(enemyPosition, currentGameState.getPosition(PLAYER));
        if (d <= 1.0) {
            mapScore += 300;
        }
    }

    int c1 = 1000;
    int c2 = 1;
    return c1 * staticScore + c2 * mapScore;
} // evaluationFunction
