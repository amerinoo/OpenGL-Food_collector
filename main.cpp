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
using namespace std;

void usage(char *);
bool hasCorrectArguments(int, int, int, int);

int minHeight = 5;
int minWidth  = 6;

int main(int argc, char * argv[]){
    Graphics& graphics = Graphics::getInstance();

    graphics.init(argc, argv);
    int height               = 15;
    int width                = 15;
    int maxHeight            = graphics.getMaxHeight();
    int maxWidth             = graphics.getMaxWidth();
    const int buf_max        = 512;
    int baudrate             = 9600; // default
    char serialport[buf_max] = "/dev/ttyACM0";
    char eolchar             = '}';
    float seed               = -1;
    char quiet               = 1;

    /* parse options */
    int option_index = 0, opt;
    static struct option loptions[] = {
        { "help",   no_argument,       0, 'h' },
        { "height", required_argument, 0, 'H' },
        { "width",  required_argument, 0, 'W' },
        { "seed",   required_argument, 0, 's' },
        { "baud",   required_argument, 0, 'b' },
        { "port",   required_argument, 0, 'p' },
        { "fast",   no_argument,       0, 'f' },
        { "turtle", no_argument,       0, 't' },
        { NULL,                     0, 0,   0 }
    };

    while (1) {
        opt = getopt_long(argc, argv, "hH:W:s:b:p:ft",
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
    Game game(height, width, seed);
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
         << "  -b, --baud         Baudrate (bps) of Arduino (default 9600)" << endl
         << "  -p, --port         Serial port Arduino is connected to (default /dev/ttyACM0)" << endl
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
