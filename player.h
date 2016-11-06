/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#ifndef player_h
#define player_h
#include "agent.h"

class Player : public Agent{
 public:
    // Constructors
    Player();
    Player(Cell*);

    void goInitPosition();
};
#endif
