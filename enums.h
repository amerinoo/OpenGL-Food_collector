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
    WATER = 0,
    LAVA  = 1,
    WOOD  = 2
};

enum Camera {
    CAMERA_UP    = 0,
    CAMERA_RIGHT = 1,
    CAMERA_DOWN  = 2,
    CAMERA_LEFT  = 3,
    CAMERA_NONE  = 4
};

enum Shoot {
    NO_SHOOT = 0,
    SHOOT    = 1
};

enum PauseResume {
    PAUSE  = 0,
    RESUME = 1
};

enum Velocity {
    INCREASE = 0,
    REDUCE   = 1,
    KEEP     = 2
};

enum SensorType {
    JOYSTICK_CAMERA_DIRECTION = 'C',
    JOYSTICK_SEL              = 'S',
    DHT_TEXTURE               = 'T',
    ULTRASOUND_DISTANCE       = 'P',
    ADXL_DIRECTION            = 'M',
    HEART_RATE_VELOCITY       = 'V'
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
    K_P     = 'p',
    K_C     = 'c'
};

enum StrategyType {
    REFLEX_AGENT,
    EXPECTIMAX_AGENT
};
#endif // ifndef enums_h
