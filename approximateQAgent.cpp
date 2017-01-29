#include "approximateQAgent.h"

const char * ApproximateQAgent::weightsFileName = "weights.dat";

ApproximateQAgent::ApproximateQAgent(){ }

ApproximateQAgent::ApproximateQAgent(Map * gameState, CellType agent, float epsilon,
  float alpha, float discount, int numTraining)
    : PacmanQAgent(gameState, agent, epsilon, alpha, discount, numTraining){
    readWeightsFile();
}

void ApproximateQAgent::readWeightsFile(){
    FILE * input = fopen(weightsFileName, "r");

    if (input != NULL) {
        std::cout << "Reading " << weightsFileName << " file" << std::endl;
        char key[30];
        float value;
        while (fscanf(input, "%s %f", key, &value) != EOF) {
            string keyString(key);
            weights[keyString] = value;
        }
        fclose(input);
    } else {
        std::cout << "Unable to read " << weightsFileName << " file" << std::endl;
    }
}

float ApproximateQAgent::getQValue(Map state, Direction action){
    float qValue = 0.0;

    map<string, float> features = getFeatures(state, action);
    for (map<string, float>::iterator it = features.begin(); it != features.end(); ++it)
        qValue += (features[it->first] * weights[it->first]);
    return qValue;
}

void ApproximateQAgent::update(Map state, Direction action, Map nextState, float reward){
    map<string, float> features = getFeatures(state, action);
    float difference = (reward + discount * getValue(nextState)) - getQValue(state, action);

    for (map<string, float>::iterator it = features.begin(); it != features.end(); ++it)
        weights[it->first] += (alpha * difference * it->second);
}

/************** Start ReinforcementAgent **************/
void ApproximateQAgent::final(Map state){
    // call the super-class final method
    PacmanQAgent::final(state);
    // did we finish training?
    if (episodesSoFar == numTraining) {
        // you might want to print your weights here for debugging
        ofstream myfile(weightsFileName);
        for (map<string, float>::iterator it = weights.begin(); it != weights.end(); ++it) {
            cout << it->first << " " << weights[it->first] << endl;
            if (myfile.is_open()) {
                myfile << it->first << " " << weights[it->first] << endl;
            }
        }
        myfile.close();
        std::cout << std::endl;
    }
}

map<string, float> ApproximateQAgent::getFeatures(Map state, Direction action){
    map<string, float> features;
    features["bias"] = 1.0;
    Cell * nextEnemyPosition = state.getNextState(state.getPosition(agent1), action);
    if ((abs(manhattanDistance(state.getPosition(agent1), state.getPosition(agent2)) - 2) < 0.00000001))
        features["#-of-ghosts-1-step-away"] = 1;
    if (!state.getBulletEnable() &&
      (abs(manhattanDistance(state.getPosition(agent1), state.getPosition(BULLET)) - 3) < 0.00000001))
        features["#-of-bullets-1-step-away"] = 1.0;

    if (features["#-of-bullets-1-step-away"] == 0 && nextEnemyPosition->hasFood())
        features["eats-food"] = 1.0;
    int dist = closestFoodDistance(state, nextEnemyPosition);
    if (dist > 0) // No estic segur de que el resultat de la operacio sigui un float
        features["closest-food"] = float(dist) / (state.getHeight() * state.getWidth());

    divideAll(features, 10.0);
    return features;
}

/************** End ReinforcementAgent **************/

int ApproximateQAgent::closestFoodDistance(Map state, Cell * position){
    return blindSearchGraph(state, position).size();
}

void ApproximateQAgent::divideAll(map<string, float> features, float number){
    for (map<string, float>::iterator it = features.begin(); it != features.end(); ++it)
        features[it->first] = it->second / number;
}
