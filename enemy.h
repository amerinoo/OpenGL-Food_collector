/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#ifndef enemy_h
#define enemy_h
#include "agent.h"

class Enemy : public Agent{
 public:
    // Constructors
    Enemy();
    Enemy(Cell*);

    void goInitPosition();
};
#endif
