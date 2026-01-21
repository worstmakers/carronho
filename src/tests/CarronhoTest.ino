/*
 * BASIC TEST FOR THE L9110S MOTOR DRIVER
 * Suggest refactor including breaks between directions change BEFORE using
 * L9110S
 */

#include <HCSR04.h>

int redLED = 2; // red LED connected to the UNO's pin 2

// HC-SR04 Configuration for one sensor
byte triggerPin = 13;                     // trigger connected to the pin 13
byte echoCount = 1;                       // this sketch is for one sensor only
byte *echoPins = new byte[echoCount]{12}; // echo pin connected to pin 12
long *times = new long[echoCount];
double *distances = new double[echoCount];

// L9110S pin and speed setup
int A1A = 6;
int A1B = 5;
int B1A = 10;
int B1B = 9;
int speed = 200; // I'm using PWM pins to control speed
long direction;

void setup() {
  Serial.begin(9600);
  HCSR04.begin(triggerPin, echoPins, echoCount);
  pinMode(redLED, OUTPUT);
  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);
  pinMode(B1A, OUTPUT);
  pinMode(B1B, OUTPUT);
  randomSeed(analogRead(0));
}

void loop() {
  forward();
  delay(3000);
  stop();
  delay(3000);
  backward();
  delay(3000);
}

void backward() {
  analogWrite(A1A, 0);
  analogWrite(A1B, speed);
  analogWrite(B1A, 0);
  analogWrite(B1B, speed);
}

void forward() {
  analogWrite(A1A, speed);
  analogWrite(A1B, 0);
  analogWrite(B1A, speed);
  analogWrite(B1B, 0);
}

void stop() {
  analogWrite(A1A, 0);
  analogWrite(A1B, 0);
  analogWrite(B1A, 0);
  analogWrite(B1B, 0);
}

void forright() {
  analogWrite(A1A, 0);
  analogWrite(A1B, 0);
  analogWrite(B1A, speed);
  analogWrite(B1B, 0);
}

void backright() {
  analogWrite(A1A, 0);
  analogWrite(A1B, 0);
  analogWrite(B1A, 0);
  analogWrite(B1B, speed);
}

void forleft() {
  analogWrite(A1A, speed);
  analogWrite(A1B, 0);
  analogWrite(B1A, 0);
  analogWrite(B1B, 0);
}

void backleft() {
  analogWrite(A1A, 0);
  analogWrite(A1B, speed);
  analogWrite(B1A, 0);
  analogWrite(B1B, 0);
}
