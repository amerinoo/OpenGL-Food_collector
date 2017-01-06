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
    actions.push_back(action);
    Node * parent = this->parent;
    while (parent != NULL) {
        if (parent->action != NONE) {
            actions.push_back(parent->action);
        }
        parent = parent->parent;
    }
    return actions;
}

Strategy::Strategy(){ }

Strategy::Strategy(Map * gameState) : gameState(gameState){ }

Map * Strategy::getGameState(){ return gameState; }

Direction Strategy::getAction(){ return NONE; }

void Strategy::final(Map state){ }

Direction Strategy::randomChoice(vector<Direction> actions){
    random_shuffle(actions.begin(), actions.end());
    return actions[0];
}

vector<Direction> Strategy::getLegalActions(Cell * c){
    return gameState->getLegalActions(c);
}

float Strategy::getDistance(Map gameState, Cell * c1, Cell * c2){
    return manhattanDistance(c1, c2);
}

float Strategy::manhattanDistance(Cell * c1, Cell * c2){
    return abs(c2->getX() - c1->getX()) + abs(c2->getY() - c1->getY());
}

vector<Direction> Strategy::blindSearchGraph(Map gameState, Cell * initial, Cell * goal){
    queue<Node *> fringe;
    Node * n = new  Node(initial, NULL, NONE);
    if (n->state == goal)
        return n->path();

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
                if (ns->state == goal) {
                    return ns->path();
                }

                fringe.push(ns);
                generated[ns->state->getKey()] = 'F';
            }
        }
    }
} // blindSearchGraph
