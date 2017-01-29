#include "pacmanQAgent.h"

PacmanQAgent::PacmanQAgent() : Strategy(){ }

PacmanQAgent::PacmanQAgent(Map * gameState, CellType agent, float epsilon, float alpha, float discount, int numTraining)
    : Strategy(gameState, agent), epsilon(epsilon), alpha(alpha),
    discount(discount), lastStateOk(false), episodesSoFar(0),
    accumTrainRewards(0.0), accumTestRewards(0.0), episodeRewards(0.0), numTraining(numTraining),
    lastWindowAccumRewards(0.0){ }

float PacmanQAgent::getQValue(Map state, Direction action){ return qValues[getKey(state, action)]; }

float PacmanQAgent::computeValueFromQValues(Map state){
    vector<Direction> legalActions = getLegalActions(state.getPosition(agent1));
    if (legalActions.empty()) return 0.0;

    map<Direction, float> bestValue;
    for (unsigned int i = 0; i < legalActions.size(); i++) {
        bestValue[legalActions[i]] = getQValue(state, legalActions[i]);
    }
    return bestValue[argMax(bestValue)];
}

Direction PacmanQAgent::computeActionFromQValues(Map state){
    vector<Direction> legalActions = getLegalActions(state.getPosition(agent1));
    if (legalActions.empty()) return NONE;

    vector<Direction> bestActions;
    float maxValue = getValue(state);
    map<Direction, float> bestAction;
    for (unsigned int i = 0; i < legalActions.size(); i++) {
        if (abs(maxValue - getQValue(state, legalActions[i])) < 0.00000001)
            bestActions.push_back(legalActions[i]);
    }
    return randomChoice(bestActions);
}

Direction PacmanQAgent::getAction(){
    vector<Direction> legalActions = getLegalActions(gameState->getPosition(agent1));
    if (legalActions.empty()) return NONE;

    Direction action = (flipCoin(epsilon)) ? randomChoice(legalActions) : getPolicy(*gameState);
    doAction(*gameState, action);
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
void PacmanQAgent::startEpisode(){
    lastStateOk    = false;
    lastAction     = NONE;
    episodeRewards = 0.0;
}

void PacmanQAgent::stopEpisode(){
    if (episodesSoFar < numTraining) accumTrainRewards += episodeRewards;
    else accumTestRewards += episodeRewards;
    episodesSoFar += 1;
    if (episodesSoFar >= numTraining) {
        // Take off the training wheels
        epsilon = 0.0; // no exploration
        alpha   = 0.0; // no learning
    }
}

bool PacmanQAgent::isInTraining(){
    return episodesSoFar < numTraining;
}

bool PacmanQAgent::isInTesting(){
    return !isInTraining();
}

/*
 * Called by environment to inform agent that a transition has
 * been observed. This will result in a call to self.update
 * on the same arguments
 *
 * NOTE: Do *not* override or call this function
 */
void PacmanQAgent::observeTransition(Map state, Direction action, Map nextState, float deltaReward){
    episodeRewards += deltaReward;
    update(state, action, nextState, deltaReward);
}

/* This is where we ended up after our last action.
 * The simulation should somehow ensure this is called
 */
Map PacmanQAgent::observationFunction(Map state){
    if (lastStateOk) {
        float reward = state.getScore(agent1) - lastState.getScore(agent1);
        observeTransition(lastState, lastAction, state, reward);
    }
    return state;
}

void PacmanQAgent::registerInitialState(){
    startEpisode();
    if (episodesSoFar == 0)
        cout << "Beginning " << numTraining << " episodes of Training" << endl;
}

// Called by Pacman game at the terminal state
void PacmanQAgent::final(Map state){
    float deltaReward = state.getScore(agent1) - lastState.getScore(agent1);

    observeTransition(lastState, lastAction, state, deltaReward);
    stopEpisode();

    lastWindowAccumRewards += state.getScore(agent1);

    int NUM_EPS_UPDATE = 5;
    if (episodesSoFar % NUM_EPS_UPDATE == 0 && episodesSoFar <= numTraining) {
        cout << "Reinforcement Learning Status:" << endl;

        float windowAvg = lastWindowAccumRewards / float(NUM_EPS_UPDATE);
        float trainAvg  = accumTrainRewards / float(episodesSoFar);
        cout << "\tCompleted " << episodesSoFar << " out of " << numTraining << " training episodes" << endl;
        cout << "\tAverage Rewards over all training: " << trainAvg << endl;

        cout << "\tAverage Rewards for last " << NUM_EPS_UPDATE << " episodes: " << windowAvg << endl;
        lastWindowAccumRewards = 0.0;
    }

    if (episodesSoFar == numTraining)
        cout << "Training Done (turning off epsilon and alpha)" << endl;
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
