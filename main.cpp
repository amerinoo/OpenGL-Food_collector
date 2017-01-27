/*
 * Project name: Food collection
 * Version 4
 * Student : Albert Eduard Merino Pulido
 */
#include <iostream>
#include <cstring>
#include <getopt.h>
#include "graphics.h"
#include "drawer.h"
#include "arduinoSerial.h"
#include "enums.h"
using namespace std;

void usage(char *);
bool hasCorrectArguments(int, int, int, int);

int minHeight = 5;
int minWidth  = 6;

int main(int argc, char * argv[]){
    Graphics& graphics = Graphics::getInstance();

    graphics.init(argc, argv);
    int height                      = 15;
    int width                       = 15;
    int maxHeight                   = graphics.getMaxHeight();
    int maxWidth                    = graphics.getMaxWidth();
    const int buf_max               = 512;
    int baudrate                    = 115200; // default
    char serialport[buf_max]        = "/dev/ttyACM0";
    char eolchar                    = '}';
    float seed                      = -1;
    char quiet                      = 1;
    StrategyType strategyTypePlayer = HUMAN_AGENT;
    StrategyType strategyTypeEnemy  = EXPECTIMAX_AGENT;

    /* parse options */
    int option_index = 0, opt;
    static struct option loptions[] = {
        { "help",   no_argument,       0, 'h' },
        { "height", required_argument, 0, 'H' },
        { "width",  required_argument, 0, 'W' },
        { "seed",   required_argument, 0, 's' },
        { "baud",   required_argument, 0, 'b' },
        { "port",   required_argument, 0, 'p' },
        { "player", required_argument, 0, 'P' },
        { "enemy",  required_argument, 0, 'E' },
        { "fast",   no_argument,       0, 'f' },
        { "turtle", no_argument,       0, 't' },
        { NULL,                     0, 0,   0 }
    };

    while (1) {
        opt = getopt_long(argc, argv, "hH:W:s:b:p:P:E:ft",
          loptions, &option_index);
        if (opt == -1) break;
        switch (opt) {
            case '0': break;
            case 'h':
                usage(argv[0]);
                break;
            case 'H':
                height = strtol(optarg, NULL, 10);
                if (!quiet) printf("Height : %d\n", height);
                break;
            case 'W':
                width = strtol(optarg, NULL, 10);
                if (!quiet) printf("Width : %d\n", width);
                break;
            case 's':
                seed = strtol(optarg, NULL, 10);
                if (!quiet) printf("Seed : %f\n", seed);
                break;
            case 'b':
                baudrate = strtol(optarg, NULL, 10);
                if (!quiet) printf("Baudrate : %d\n", baudrate);
                break;
            case 'p':
                strcpy(serialport, optarg);
                if (!quiet) printf("Port : %s\n", serialport);
                break;
            case 'P':
                if (strcmp("reflex", optarg) == 0) strategyTypePlayer = REFLEX_AGENT;
                else if (strcmp("expectimax", optarg) == 0) strategyTypePlayer = EXPECTIMAX_AGENT;
                else if (strcmp("reinforcement", optarg) == 0) strategyTypePlayer = REINFORCEMENT_AGENT;
                if (!quiet) printf("Strategy Player : %s\n", optarg);
                break;
            case 'E':
                if (strcmp("reflex", optarg) == 0) strategyTypeEnemy = REFLEX_AGENT;
                else if (strcmp("expectimax", optarg) == 0) strategyTypeEnemy = EXPECTIMAX_AGENT;
                else if (strcmp("reinforcement", optarg) == 0) strategyTypePlayer = REINFORCEMENT_AGENT;
                if (!quiet) printf("Strategy Enemy : %s\n", optarg);
                break;
            case 'f':
                Agent::agentVelocity = 20;
                if (!quiet) printf("Fast mode activated\n");
                break;
            case 't':
                Agent::agentVelocity = 500;
                if (!quiet) printf("Turtle mode activated\n");
                break;
        }
    }
    if (hasCorrectArguments(height, width, maxHeight, maxWidth)) {
        cout << "Error: Ilegal Arguments" << endl;
        cout << "Height must be larger than " << minHeight << " and smaller than " << maxHeight << endl;
        cout << "Width must be larger than " << minWidth << " and smaller than " << maxWidth << endl;
        return -1;
    }
    ArduinoSerial * serial = new ArduinoSerial(serialport, baudrate, eolchar);
    Game game(height, width, seed, strategyTypePlayer, strategyTypeEnemy);
    game.resetGame();
    Drawer& drawer = Drawer::getInstance();
    drawer.setHeight(height);
    drawer.setWidth(width);

    graphics.setGame(game);
    graphics.setArduinoSerial(serial);
    graphics.start();

    return 0;
} // main

void usage(char * name){
    cout << "Usage: " << name << " [OPTIONS]" << endl
         << "\nHelp options:" << endl
         << "  -h, --help         Print this help message" << endl
         << "\nMap options:" << endl
         << "  -H, --height       Height of the map (Default 15)" << endl
         << "  -W, --width        Width of the map (Default 15)" << endl
         << "  -s, --seed         Seed of map (Default random)" << endl
         << "\nArduino options:" << endl
         << "  -b, --baud         Baudrate (bps) of Arduino (default 115200)" << endl
         << "  -p, --port         Serial port Arduino is connected to (default /dev/ttyACM0)" << endl
         << "\nAgent options:" << endl
         << "  -P  --player       Select player strategy (Default Human)" << endl
         << "  -E  --enemy        Select enemy strategy (Default Expectimax)" << endl
         << "  Options:" << endl
         << "    · reflex" << endl
         << "    · expectimax" << endl
         << "    · reinforcement" << endl
         << "\nVelocity options:" << endl
         << "  -f  --fast         Activate fast mode (Velocity 50)" << endl
         << "  -t  --turtle       Activate turtle mode (Velocity 500)" << endl
         << "" << endl
         << "Note: Order is not important." << endl
         << "Examples:" << endl
         << "  " << name << endl
         << "  " << name << " -H 12 -W 23" << endl
         << "  " << name << " -p /dev/ttyACM1" << endl
         << "  " << name << " -s 12 -f" << endl
         << endl;
    exit(EXIT_SUCCESS);
}

bool hasCorrectArguments(int height, int width, int maxHeight, int maxWidth){
    return height < minHeight || width < minWidth || height > maxHeight || width > maxWidth;
}
