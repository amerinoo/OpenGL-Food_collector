/*
 * Project name: Food collection
 * Version 3
 * Student : Albert Eduard Merino Pulido
 */
#ifndef arduino_h
#define arduino_h

#include <stdint.h>   // Standard types

class ArduinoSerial{
public:
    char* serialport;
    int baudrate;
    int fd;
    char eolchar;
    int timeout;

    ArduinoSerial(char*,int,char);
    void serialport_init();
    int serialport_close();
    bool serialport_write(uint8_t);
    bool serialport_read(char*,int);
    int serialport_flush();
    bool isConnected();
};
#endif
