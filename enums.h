/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#ifndef enums_h
#define enums_h
enum CellType{
    WALL,
    CORRIDOR,
    FOOD,
    PLAYER,
    ENEMY
};

enum State{
    MOVE,
    QUIET
};

enum ShapeType{
    SQUARE,
    CIRCLE
};

enum Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};
#endif
