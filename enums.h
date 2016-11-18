/*
 * Project name: Food collection
 * Version 3
 * Student : Albert Eduard Merino Pulido
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
