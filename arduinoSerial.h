/*
 * Project name: Food collection
 * Version 4
 * Student : Albert Eduard Merino Pulido
 */
#ifndef arduino_h
#define arduino_h

#include <stdint.h>  // Standard types
#include <stdio.h>   // Standard input/output definitions
#include <unistd.h>  // UNIX standard function definitions
#include <fcntl.h>   // File control definitions
#include <errno.h>   // Error number definitions
#include <termios.h> // POSIX terminal control definitions
#include <cstring>   // String function definitions
#include <sys/ioctl.h>
#include <iostream>
using namespace std;

typedef struct Sensor {
    int horz;
    int vert;
    int sel;
    int temperature;
    int distance;
    int x;
    int y;
    int qs;
    int bpm;
    Sensor();
} Sensor;

class ArduinoSerial {
public:
    char * serialport;
    int baudrate;
    int fd;
    char eolchar;
    int timeout;
    bool reading;

    ArduinoSerial(char *, int, char);
    void serialport_init();
    int serialport_close();
    bool serialport_write(uint8_t);
    bool serialport_read(char *, int);
    int serialport_flush();
    bool isConnected();
    bool isReading();
    void setReading(bool);
};
#endif // ifndef arduino_h
