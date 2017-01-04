/*
 * Project name: Food collection
 * Version 4
 * Student : Albert Eduard Merino Pulido
 */
#ifndef enums_h
#define enums_h
enum CellType {
    WALL,
    CORRIDOR,
    FOOD,
    PLAYER,
    ENEMY,
    BULLET
};

enum State {
    ROTATE,
    MOVE,
    QUIET
};

enum ShapeType {
    SQUARE,
    CIRCLE
};

enum Direction {
    UP    = 0,
    LEFT  = 90,
    DOWN  = 180,
    RIGHT = 270,
    NONE  = 360
};

enum Texture {
    WOOD,
    WATER,
    LAVA
};

enum SensorType {
    JOYSTICK_HORZ = 'H',
    JOYSTICK_VERT = 'V',
    JOYSTICK_SEL  = 'S',
    DHT_TEMP      = 'T'
};

enum Keyboard {
    K_R     = 'r',
    K_W     = 'w',
    K_S     = 's',
    K_A     = 'a',
    K_D     = 'd',
    K_SPACE = ' ',

    K_I     = 'i',
    K_K     = 'k',
    K_J     = 'j',
    K_L     = 'l',

    K_PLUS  = '+',
    K_MINUS = '-',
    K_P     = 'p'
};
#endif // ifndef enums_h
