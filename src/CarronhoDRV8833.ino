/*                          CARRONHO PROJECT

  DESCRIPTION: This project is a prototype to test the algoritm that controls
  a 2WD chassis car. The car will ride without a controller, just a using a
  distance sensor and when facing an obstacle, it will light a red LED, stop,
  change direction (to left or right) and the cicle repeats. The gears are
  controlled by a DRV8833 H bridge, the distance is measured by a HC-SR04
  ultrassonic sensor and an Arduino UNO serves as the microcontroler.

  Date: 7 January 2026
  Author: [Worst Makers (Jenny DeVito)]
  GitHub: https://github.com/worstmakers/carronho

  REFERENCES:
  https://github.com/d03n3rfr1tz3/HC-SR04

  WIRING (All GND were connected on the same pin - same breadboard column - SAME
UNO GND) Red LED: NEG = GND - breadboard D2 = 220R RESISTOR = +POLE RED LED
  HC-SR04:
    Trig = D13
    Echo = D12
    VCC = 5V
    GND = GND - breadboard
  DRV8833 H-Bridge:
    OUT1 = MOTOR 1
    OUT2 = MOTOR 1
    OUT3 = MOTOR 2
    OUT4 = MOTOR 2
    VCC = RED WIRE 4-BATTERIES HOLDER
    GND = GND - breadboard
    IN1 = D5 (PWM capable)
    IN2 = D6 (PWM capable)
    IN3 = D10 (PWM capable)
    IN4 = D9 (PWM capable)

  CIRCUIT
  The gears are powered by 4xAA bateries and the UNO is powered by a 9V battery
  GND are commom to the circuit and the red LED is wired with a 220R resistor
  in series.
******************************************************************************/

#include <HCSR04.h>

const int redLED = 2; // red LED connected to the UNO's pin 2

/*************************** HC-SR04 Configuration ***************************/
byte triggerPin = 13;                     // trigger connected to the pin 13
byte echoCount = 1;                       // number of sensors wired
byte *echoPins = new byte[echoCount]{12}; // echo pin connected to pin 12
long *times = new long[echoCount];
double *distances = new double[echoCount];

/********************************** DRV8833 **********************************/
const int IN1 = 6;
const int IN2 = 5;
const int IN3 = 10;
const int IN4 = 9;

uint8_t speedPWM = 200;
long directionRandom;

/************************ to avoid sudden gear shifts ************************/
static inline void deadTime() { delay(30); }

void setup() {
  Serial.begin(9600);
  HCSR04.begin(triggerPin, echoPins, echoCount);

  pinMode(redLED, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotors();
  randomSeed(analogRead(0));
}

void loop() {
  HCSR04.measureMicroseconds(times);
  Serial.print("1: ");
  Serial.print(times[0]);
  Serial.println(" us");

  delay(50);

  HCSR04.measureDistanceCm(distances);
  double d = distances[0];
  Serial.print("1: ");
  Serial.print(d);
  Serial.println(" cm");

  if (d <= 3) {
    digitalWrite(redLED, HIGH);
    stopMotors();
    delay(300);
    backward();
    delay(500);
    backward();
    delay(100);
  } else if ((d > 3) && (d <= 10)) {
    directionRandom = random(1, 101);
    if (directionRandom % 2 == 0) {
      backRight();
      digitalWrite(redLED, LOW);
      delay(300);
      backward();
      digitalWrite(redLED, HIGH);
      delay(150);
      backRight();
      digitalWrite(redLED, LOW);
      delay(300);
    } else {
      backLeft();
      digitalWrite(redLED, LOW);
      delay(300);
      backward();
      digitalWrite(redLED, HIGH);
      delay(150);
      backLeft();
      digitalWrite(redLED, LOW);
      delay(300);
    }
  } else {
    digitalWrite(redLED, LOW);
    forward();
  }

  delay(80);
}

/*************************** gear's basic controls ***************************/
void motorA_forward(uint8_t pwm) {
  analogWrite(IN1, pwm);
  digitalWrite(IN2, LOW);
}

void motorA_backward(uint8_t pwm) {
  digitalWrite(IN1, LOW);
  analogWrite(IN2, pwm);
}

void motorB_forward(uint8_t pwm) {
  analogWrite(IN3, pwm);
  digitalWrite(IN4, LOW);
}

void motorB_backward(uint8_t pwm) {
  digitalWrite(IN3, LOW);
  analogWrite(IN4, pwm);
}

void stopMotors() {
  /* also can be written as digitalWrite(), it will work the same but the below
  explicit that all pins are PWM capabable and aren't receiving signals */
  /* MOTOR A */
  analogWrite(IN1, 0); // digitalWrite(IN1, LOW);
  analogWrite(IN2, 0); // digitalWrite(IN2, LOW);
  /* MOTOR B */
  analogWrite(IN3, 0); // digitalWrite(IN3, LOW);
  analogWrite(IN3, 0); // digitalWrite(IN4, LOW);
}

void stopMotorA() {
  /* also can be written as digitalWrite(), it will work the same but the below
  explicit that all pins are PWM capabable and aren't receiving signals */
  analogWrite(IN1, 0); // digitalWrite(IN1, LOW);
  analogWrite(IN2, 0); // digitalWrite(IN2, LOW);
}

void stopMotorB() {
  /* also can be written as digitalWrite(), it will work the same but the below
  explicit that all pins are PWM capabable and aren't receiving signals */
  analogWrite(IN3, 0); // digitalWrite(IN3, LOW);
  analogWrite(IN3, 0); // digitalWrite(IN4, LOW);
}

/*************************** gear motion functions ***************************/
void backward() {
  motorA_forward(speedPWM);
  motorB_forward(speedPWM);
}

void forward() {
  stopMotors();
  deadTime();
  motorA_backward(speedPWM);
  motorB_backward(speedPWM);
}

void turnRight() {
  stopMotors();
  deadTime();
  motorA_forward(speedPWM);
  stopMotorB();
}

void turnLeft() {
  stopMotors();
  deadTime();
  motorB_forward(speedPWM);
  stopMotorA();
}

void backRight() {
  stopMotors();
  deadTime();
  stopMotorA();
  motorB_forward(speedPWM);
}

void backLeft() {
  stopMotors();
  deadTime();
  stopMotorB();
  motorA_forward(speedPWM);
}
