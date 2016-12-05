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
    ENEMY,
    BULLET
};

enum State{
    ROTATE,
    MOVE,
    QUIET
};

enum ShapeType{
    SQUARE,
    CIRCLE
};

enum Direction{
    UP=0,
    LEFT=90,
    DOWN=180,
    RIGHT=270,
    NONE=360
};
#endif
