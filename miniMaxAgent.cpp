/*
 * Project name: Food collection
 * Version 3
 * Student : Albert Eduard Merino Pulido
 */
#include "miniMaxAgent.h"

MinimaxAgent::MinimaxAgent() : Strategy(){ }

MinimaxAgent::MinimaxAgent(Map map) : Strategy(map){ }


Direction MinimaxAgent::getAction(Cell * c){
    float v = -99999999999999999;

    vector<Direction> actions;
    vector<Direction> legalActions = getLegalActions(c);

    for(unsigned int i =0;i<legalActions.size();i++){
        u = min_value(a, 1, self.depth)
        if (u == v)
            actions.push_back(i)
        else if (u > v){
            v = u;
            actions = [];
            actions.push_back(i);
        }
    }
    random_shuffle(actions.begin(), actions.end());
    return legalActions[actions[0]];
}


Direction MinimaxAgent::utility(Cell * gameState){
    return reflexAgent(gameState);
}

Direction MinimaxAgent::terminalTest(Cell * gameState, int depth){
    return map.getFood().size() == 0;
}

Cell* MinimaxAgent::result(Cell * currentPosition){
    return null;
}

Cell* MinimaxAgent::max_value(Cell * agent, agent, depth){
    if (terminalTest(gameState, depth))
        return utility(gameState);

    vector<Direction> legalActions = getLegalActions(c);
    float v = -99999999999999999;
    float best = -9999999999999999;
    for a in gameState.getLegalActions(agent)
        int v = min_value(a, 1, depth)
        if(best < v)
            best = v;

    return best;
}


Cell* MinimaxAgent::min_value(Cell * currentPosition){
    if (terminalTest(gameState, depth))
        return utility(gameState);

    float v = 99999999999999999;
    float best = 9999999999999999;
    vector<Direction> legalActions = getLegalActions(c);
    for a in gameState.getLegalActions(agent)
        int v = max_value(a, 0, depth-1)
        if(best > v)
            best = v;

    return best;
}



Direction MinimaxAgent::reflexAgent(Cell * c){
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

vector<Direction> MinimaxAgent::getLegalActions(Cell * c){
    return map.getLegalActions();
}

float MinimaxAgent::evaluationFunction(Cell * currentPosition, Direction direction){
    float totalScore    = 0.0;
    Cell * nextPosition = getNextState(currentPosition, direction);

    vector<Cell *> food = map.getFood();
    for (unsigned int i = 0; i < food.size(); i++) {
        int d = manhattanDistance(nextPosition, food[i]);
        totalScore += (d == 0.0) ? 100 : 1.0 / (d * d);
    }
    return totalScore;
} // evaluationFunction

Cell * MinimaxAgent::getNextState(Cell * cell, Direction direction){
    if (direction == UP) return cell->getUp();
    else if (direction == DOWN) return cell->getDown();
    else if (direction == LEFT) return cell->getLeft();
    else return cell->getRight();
}

double MinimaxAgent::manhattanDistance(Cell * c1, Cell * c2){
    return abs(c2->getX() - c1->getX()) + abs(c2->getY() - c1->getY());
}
