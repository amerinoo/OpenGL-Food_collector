/*
 * Project name: Food collection
 * Version 1
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#ifndef enemy_h
#define enemy_h
#include <iostream>
#include "agent.h"

class Enemy : public Agent{
 public:
    // Constructors
    Enemy();

    // Getters
    CellType getType();
    char getSymbol();

    void eat();
    void draw();
};
#endif