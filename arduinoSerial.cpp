/*
 * Project name: Food collection
 * Version 4
 * Student : Albert Eduard Merino Pulido
 */
#include "arduinoSerial.h"

Sensor::Sensor(){ }

ArduinoSerial::ArduinoSerial(char * serialport, int baudrate, char eolchar)
    : serialport(serialport), baudrate(baudrate), eolchar(eolchar), reading(false){
    serialport_init();
}

void ArduinoSerial::serialport_init(){
    struct termios toptions;

    fd = open(serialport, O_RDWR | O_NONBLOCK);

    if (!isConnected()) {
        perror("serialport_init: Unable to open port ");
        return;
    }

    if (tcgetattr(fd, &toptions) < 0) {
        perror("serialport_init: Couldn't get term attributes");
        return;
    }

    speed_t brate = baudrate; // let you override switch below if needed
    switch (baudrate) {
        case 4800:
            brate = B4800;
            break;
        case 9600:
            brate = B9600;
            break;
        case 19200:
            brate = B19200;
            break;
        case 38400:
            brate = B38400;
            break;
        case 57600:
            brate = B57600;
            break;
        case 115200:
            brate = B115200;
            break;
    }
    cfsetispeed(&toptions, brate);
    cfsetospeed(&toptions, brate);

    // 8N1
    toptions.c_cflag &= ~PARENB;
    toptions.c_cflag &= ~CSTOPB;
    toptions.c_cflag &= ~CSIZE;
    toptions.c_cflag |= CS8;
    // no flow control
    toptions.c_cflag &= ~CRTSCTS;

    // toptions.c_cflag &= ~HUPCL; // disable hang-up-on-close to avoid reset

    toptions.c_cflag |= CREAD | CLOCAL;          // turn on READ & ignore ctrl lines
    toptions.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl

    toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
    toptions.c_oflag &= ~OPOST;                          // make raw

    // see: http://unixwiz.net/techtips/termios-vmin-vtime.html
    toptions.c_cc[VMIN]  = 0;
    toptions.c_cc[VTIME] = 0;
    // toptions.c_cc[VTIME] = 20;

    tcsetattr(fd, TCSANOW, &toptions);
    if (tcsetattr(fd, TCSAFLUSH, &toptions) < 0) {
        perror("init_serialport: Couldn't set term attributes");
    }
} // serialport_init

int ArduinoSerial::serialport_close(){
    return close(fd);
}

bool ArduinoSerial::serialport_write(uint8_t b){
    return write(fd, &b, 1) == 1;
}

bool ArduinoSerial::serialport_read(char * buf, int buf_max){
    if (!isConnected() || !serialport_write(eolchar)) return false;

    char b[1]; // read expects an array, so we give it a 1-byte array
    int i = 0;

    timeout = 20;

    do {
        int n = read(fd, b, 1);     // read a char at a time
        if (n == -1) return false;  // couldn't read

        if (n == 0) {
            usleep(1 * 1000); // wait 1 msec try again
            timeout--;
            if (timeout == 0) return false;

            continue;
        }
        buf[i] = b[0];
        i++;
    } while (b[0] != eolchar && i < buf_max && timeout > 0);
    buf[i] = 0; // null terminate the string

    return true;
}

int ArduinoSerial::serialport_flush(){
    sleep(2); // required to make flush work, for some reason
    return tcflush(fd, TCIOFLUSH);
}

bool ArduinoSerial::isConnected(){ return fd != -1; }

bool ArduinoSerial::isReading(){ return reading; }

void ArduinoSerial::setReading(bool reading){ this->reading = reading; }
