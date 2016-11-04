/*
 * Project name: Food collection
 * Version 1
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#ifndef agent_h
#define agent_h
#include "cell.h"
using namespace std;

class Agent{
 public:
    
    // Constructors
    Agent();

    // Getters 
    virtual char getSymbol();
    virtual CellType getType();
    virtual void eat();
    virtual void draw();


    // Setters
    void setPosition(Cell*);

    protected:
    int x, y;
    Cell* position;
    int points;
    int padding;
};
#endif
