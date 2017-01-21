#include "DHT.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <SoftwareSerial.h>

// Joystick
#define HORZ 0 //Analog
#define VERT 1 //Analog
#define SEL 2 //Digital

// DHT
#define DHTTYPE DHT11
#define DHTPIN 3 //Digital

// Ultrasound
#define TRIG 4 //Digital
#define ECHO 5 //Digital

// Heart Rate
#define PULSE  2 //Analog -> Pulse Sensor purple wire
#define BLINK  13 //Digital -> Pin to blink led at each beat

typedef enum Direction {
  UP = 0,
  RIGHT = 90,
  DOWN = 180,
  LEFT = 270,
  NONE = 360
} Direction;

typedef enum Camera {
  CAMERA_UP = 0,
  CAMERA_RIGHT = 1,
  CAMERA_DOWN = 2,
  CAMERA_LEFT = 3,
  CAMERA_NONE = 4
} Camera;

typedef enum Shoot {
  NO_SHOOT = 0,
  SHOOT = 1
} Shoot;

typedef enum PauseResume {
  PAUSE = 0,
  RESUME = 1
} PauseResume;

typedef enum Velocity {
  INCREASE = 0,
  REDUCE = 1,
  KEEP = 2
} Velocity;

typedef enum Texture {
  WATER = 0,
  LAVA = 1
} Texture;

int valX = 0;
int valY = 0;
int select = HIGH;

SoftwareSerial mySerial(10, 11); // RX, TX

DHT dhtSensor(DHTPIN, DHTTYPE);
int temperature;

long distance = 0;

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

sensors_event_t event;

// these variables are volatile because they are used during the interrupt service routine!
volatile int bpm;                   // used to hold the pulse rate
volatile int raw;                // holds the incoming raw data
volatile int ibi = 600;             // holds the time between beats, the Inter-Beat Interval
volatile boolean pulse = false;     // true when pulse wave is high, false when it's low
volatile boolean qs = false;        // becomes true when Arduoino finds a beat.

Camera cameraDirection;
Shoot shoot;
Texture texture;
PauseResume pauseResume;
Direction move;
Velocity velocity;
int n;
int showBPM;
int pauseGame;

void setup() {
  //Serial.begin(9600);
  Serial.begin(115200);             // we agree to talk fast!

  pinMode(SEL, INPUT);
  digitalWrite(SEL, HIGH);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  if (!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while (1);
  }
  accel.setRange(ADXL345_RANGE_16_G);

  pinMode(BLINK, OUTPUT);        // pin that will blink to your heartbeat!

  interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS

  cameraDirection = CAMERA_NONE;
  shoot = NO_SHOOT;
  texture = WATER;
  pauseResume = RESUME;
  move = NONE;
  velocity = KEEP;
  n = 0;
  showBPM = 1;
  pauseGame = 0;
  mySerial.begin(9600);
}

void loop() {
  joystick();
  dht();
  ultrasound();
  adxl();
  heartRate();
  if (mySerial.available()) {
    char inChar = (char)mySerial.read(); //read the input
    int inInt =  (char)mySerial.read() - '0';
    Serial.println(inInt);
    if (inChar == 'H') {
      showBPM = inInt;
    } else if (inChar == 'P') {
      pauseGame = inInt;
    }
  }
  delay(80);
}

void serialEvent() {
  if (Serial.available()) {
    Serial.read();
    Serial.print("{");
    // joystick
    Serial.print("\"C\":"); Serial.print(cameraDirection); Serial.print(',');
    Serial.print("\"S\":"); Serial.print(shoot);  Serial.print(',');
    // dht
    Serial.print("\"T\":"); Serial.print(texture); Serial.print(',');
    // ultrasound
    Serial.print("\"P\":"); Serial.print(pauseResume); Serial.print(',');
    // adxl
    Serial.print("\"M\":"); Serial.print(move); Serial.print(',');
    // heartRate
    Serial.print("\"V\":"); Serial.print(velocity);

    Serial.print("}");

    n++;
    if (n >= 15) {
      n = 0;
      // joystick
      mySerial.print("Joystick X: "); mySerial.println(valX);
      mySerial.print("Joystick Y: "); mySerial.println(valY);
      mySerial.print("Joystick Click: "); mySerial.println(shoot);
      // dht
      mySerial.print("Temperature: "); mySerial.println(temperature);
      // ultrasound
      mySerial.print("Distance: "); mySerial.println(distance);
      // adxl
      mySerial.print("ADXL X: "); mySerial.println(event.acceleration.x);
      mySerial.print("ADXL Y: "); mySerial.println(event.acceleration.y);
      // heartRate
      mySerial.print("BPM: "); mySerial.print(bpm);
    }
  }
}

void joystick() {
  valX = map(analogRead(HORZ), 0, 1023, 0, 19);
  valY = map(analogRead(VERT), 0, 1023, 0, 19);
  select = digitalRead(SEL);

  bool horz = valX > 5 && valX < 15;
  bool vert = valY > 5 && valY < 15;

  if (vert && horz) cameraDirection = CAMERA_NONE;
  else if (vert) cameraDirection = (valX >= 10) ? CAMERA_LEFT : CAMERA_RIGHT;
  else cameraDirection = (valY >= 10) ? CAMERA_UP : CAMERA_DOWN;


  shoot = (select != 1) ? shoot = SHOOT : NO_SHOOT;
}

void dht() {
  temperature = getTemperature();
  // std::cout << sensor.temperature << endl;
  if (temperature != 0) {
    texture = (temperature > 26) ? LAVA : WATER;
  }
}

int getTemperature() {
  return dhtSensor.readTemperature();
}

void ultrasound() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(5);
  digitalWrite(TRIG, LOW);
  long duration = pulseIn(ECHO, HIGH);
  distance = microsecondsToCentimeters(duration);

  pauseResume = (distance > 50 && distance < 800 || pauseGame == 1) ? PAUSE : RESUME;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

void adxl() {
  accel.getEvent(&event);

  bool horz = event.acceleration.x > -5 && event.acceleration.x < 5;
  bool vert = event.acceleration.y > -5 && event.acceleration.y < 5;

  if (vert && horz) move = NONE;
  else if (vert) move = (event.acceleration.x >= 0) ? LEFT : RIGHT;
  else move = (event.acceleration.y >= 0) ? UP : DOWN;
}

void heartRate() {

  if (qs && showBPM == 1) {
    if (bpm > 80 && bpm < 110) velocity = INCREASE;  // Reduce velocity
    else if (bpm < 70) velocity = REDUCE;            // Increase velocity
    else velocity = KEEP;
  } else {
    velocity = KEEP;
  }
}

