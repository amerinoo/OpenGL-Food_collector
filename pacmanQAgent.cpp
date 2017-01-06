#include "pacmanQAgent.h"

PacmanQAgent::PacmanQAgent() : Strategy(){ }

PacmanQAgent::PacmanQAgent(Map * gameState, float epsilon, float alpha, float discount)
    : Strategy(gameState), agent(ENEMY), epsilon(epsilon), alpha(alpha),
    discount(discount), lastStateOk(false){ }

float PacmanQAgent::getQValue(Map state, Direction action){ return qValues[getKey(state, action)]; }

float PacmanQAgent::computeValueFromQValues(Map state){
    vector<Direction> legalActions = getLegalActions(state.getPosition(agent));
    if (legalActions.empty()) return 0.0;

    map<Direction, float> bestValue;
    for (unsigned int i = 0; i < legalActions.size(); i++) {
        bestValue[legalActions[i]] = getQValue(state, legalActions[i]);
    }
    return bestValue[argMax(bestValue)];
}

Direction PacmanQAgent::computeActionFromQValues(Map state){
    vector<Direction> legalActions = getLegalActions(state.getPosition(agent));
    if (legalActions.empty()) return NONE;

    map<Direction, float> bestAction;
    for (unsigned int i = 0; i < legalActions.size(); i++) {
        bestAction[legalActions[i]] = getQValue(state, legalActions[i]);
    }
    return argMax(bestAction);
}

Direction PacmanQAgent::getAction(Map state){
    vector<Direction> legalActions = getLegalActions(state.getPosition(agent));
    if (legalActions.empty()) return NONE;

    Direction action = (flipCoin(epsilon)) ? randomChoice(legalActions) : getPolicy(state);
    doAction(state, action);
    return action;
}

bool PacmanQAgent::flipCoin(float epsilon){
    return epsilon > rand() % 100;
}

void PacmanQAgent::doAction(Map state, Direction action){
    lastState   = state;
    lastAction  = action;
    lastStateOk = true;
}

void PacmanQAgent::update(Map state, Direction action, Map nextState, float reward){
    qValues[getKey(state, action)] = (1 - alpha) * getQValue(state, action) \
      + alpha * (reward + discount * getValue(nextState));
}

Direction PacmanQAgent::getPolicy(Map state){ return computeActionFromQValues(state); }

float PacmanQAgent::getValue(Map state){ return computeValueFromQValues(state); }

/************** Start ReinforcementAgent **************/

/*
 * Called by environment to inform agent that a transition has
 * been observed. This will result in a call to self.update
 * on the same arguments
 *
 * NOTE: Do *not* override or call this function
 */
void PacmanQAgent::observeTransition(Map state, Direction action, Map nextState, float deltaReward){
    // episodeRewards += deltaReward;
    update(state, action, nextState, deltaReward);
}

/* This is where we ended up after our last action.
 * The simulation should somehow ensure this is called
 */
Map PacmanQAgent::observationFunction(Map state){
    if (lastStateOk) {
        float reward = state.getScore(agent) - lastState.getScore(agent);
        observeTransition(lastState, lastAction, state, reward);
    }
    return state;
}

// Called by Pacman game at the terminal state
void PacmanQAgent::final(Map state){
    float deltaReward = state.getScore(agent) - lastState.getScore(agent);

    observeTransition(lastState, lastAction, state, deltaReward);
}

/************** End ReinforcementAgent **************/
string PacmanQAgent::getKey(Map state, Direction action){
    ostringstream key;

    key << state.toString();
    key << action;
    return key.str();
}

// Returns the key with the highest value.
Direction PacmanQAgent::argMax(map<Direction, float> values){
    float max     = INT_MIN;
    Direction key = NONE;

    if (values.empty()) return NONE;

    for (map<Direction, float>::iterator it = values.begin(); it != values.end(); ++it) {
        if (max < it->second) {
            key = it->first;
            max = it->second;
        }
    }
    return key;
}
