/*
 * Project name: Food collection
 * Version 1
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#ifndef player_h
#define player_h
#include <iostream>
#include "agent.h"

class Player : public Agent{
 public:
    // Constructors
    Player();

    // Getters
    CellType getType();
    char getSymbol();

    void eat();
    void draw();
};
#endif