/*
 * Project name: Food collection
 * Version 3
 * Student : Albert Eduard Merino Pulido
 */
#include "strategy.h"
Strategy::Strategy(){ }

Strategy::Strategy(Map * map) : map(map){ }

Direction Strategy::getAction(Cell * c){ return NONE; }

Map * Strategy::getMap(){ return map; }
