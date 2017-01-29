#ifndef APPROXIMATE_Q_AGENT
#define APPROXIMATE_Q_AGENT
#include <map>
#include <string>
#include "pacmanQAgent.h"
#include "map.h"
#include "enums.h"
class ApproximateQAgent : public PacmanQAgent {
public:
    ApproximateQAgent();
    ApproximateQAgent(Map * gameState, CellType agent, float epsilon = 5,
      float alpha = 0.2, float discount = 0.9, int numTraining = 50);
    float getQValue(Map state, Direction action);
    void update(Map state, Direction action, Map nextState, float reward);
    /************** Start ReinforcementAgent **************/
    void final(Map state);
    /************** End ReinforcementAgent **************/
protected:
    map<string, float> weights;
private:
    int closestFoodDistance(Map state, Cell * position);
    map<string, float> getFeatures(Map state, Direction action);
    void divideAll(map<string, float> features, float number);
};
#endif // ifndef APPROXIMATE_Q_AGENT
