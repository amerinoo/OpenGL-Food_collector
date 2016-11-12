/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#include "strategy.h"
Strategy::Strategy(){ }

Strategy::Strategy(Map map) : map(map){ }

Direction Strategy::getAction(Cell * c){ return NONE; }
