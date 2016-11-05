/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#ifndef agent_h
#define agent_h
#include "cell.h"
using namespace std;

class Agent: public Cell{
 public:
    // Constructors
    Agent();

    // Getters
    int getPoints();

    // Setters
    virtual void setPosition(Cell*);

    //Methods
    void eat();

 protected:
    Cell* position;
    int points;
};
#endif
