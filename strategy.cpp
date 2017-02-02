/*
 * Project name: Food collection
 * Version 4
 * Student : Albert Eduard Merino Pulido
 */
#include "strategy.h"

Node::Node(){ }

Node::Node(Cell * state, Node * parent, Direction action)
    : state(state), parent(parent), action(action){ }

vector<Direction> Node::path(){
    vector<Direction> actions;
    Node * node = this;
    while (node != NULL) {
        if (node->action != NONE) {
            actions.push_back(node->action);
        }
        node = node->parent;
    }
    return actions;
}

Strategy::Strategy(){ }

Strategy::Strategy(Map * gameState, CellType agent) : gameState(gameState), agent1(agent){
    agent2 = (agent == PLAYER) ? ENEMY : PLAYER;
}

Map * Strategy::getGameState(){ return gameState; }

void Strategy::setGameState(Map * gameState){
    this->gameState = gameState;
}

Direction Strategy::getAction(){ return NONE; }

Map Strategy::observationFunction(Map state){ return state; }

void Strategy::registerInitialState(){ }

void Strategy::final(Map state){ }

Direction Strategy::randomChoice(vector<Direction> actions){
    random_shuffle(actions.begin(), actions.end());
    return actions[0];
}

vector<Direction> Strategy::getLegalActions(Cell * c){
    return gameState->getLegalActions(c);
}

int Strategy::getDistance(Map gameState, Cell * c1, Cell * c2){
    return closestDistance(gameState, c1, c2).size();
}

vector<Direction> Strategy::blindSearchGraph(Map gameState, Cell * initial){
    queue<Node *> fringe;
    Node * n = new  Node(initial, NULL, NONE);
    if (n->state->hasFood()) return n->path();

    fringe.push(n);
    map<float, char> generated;
    generated[n->state->getKey()] = 'F';
    while (true) {
        if (fringe.empty()) {
            return vector<Direction>();
        }

        n = fringe.front();
        fringe.pop();
        generated[n->state->getKey()] = 'E';
        vector<Direction> legalActions = getLegalActions(n->state);
        for (unsigned int i = 0; i < legalActions.size(); i++) {
            Node * ns = new Node(gameState.getNextState(n->state, legalActions[i]), n, legalActions[i]);
            if (generated.count(ns->state->getKey()) < 1) {
                if (ns->state->hasFood()) return ns->path();

                fringe.push(ns);
                generated[ns->state->getKey()] = 'F';
            }
        }
    }
} // blindSearchGraph

vector<Direction> Strategy::closestDistance(Map gameState, Cell * initial, Cell * goal){
    queue<Node *> fringe;
    Node * n = new  Node(initial, NULL, NONE);
    if (n->state == goal) return n->path();

    fringe.push(n);
    map<float, char> generated;
    generated[n->state->getKey()] = 'F';
    while (true) {
        if (fringe.empty()) {
            return vector<Direction>();
        }

        n = fringe.front();
        fringe.pop();
        generated[n->state->getKey()] = 'E';
        vector<Direction> legalActions = getLegalActions(n->state);
        for (unsigned int i = 0; i < legalActions.size(); i++) {
            Node * ns = new Node(gameState.getNextState(n->state, legalActions[i]), n, legalActions[i]);
            if (generated.count(ns->state->getKey()) < 1) {
                if (ns->state == goal) return ns->path();

                fringe.push(ns);
                generated[ns->state->getKey()] = 'F';
            }
        }
    }
}

int Strategy::closestFoodDistance(Map state, Cell * position){
    return blindSearchGraph(state, position).size();
}
