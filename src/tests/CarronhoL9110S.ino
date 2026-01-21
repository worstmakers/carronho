/* Suggest refactor including breaks between directions changes BEFORE using
 * L9110S

  DESCRIPTION: This project is a prototype to test the algoritm that controls
  a 2WD chassis car. The car will ride without a controller, just a using a
  distance sensor and when facing an obstacle, it will light a red LED, stop,
  change direction (to left or right) and the cicle repeats. The gears are
  controlled by a L9110S H bridge, the distance is measured by a HC-SR04
  ultrassonic sensor and an Arduino UNO serves as the microcontroler.

  Date: 12 December 2025
  Author: [Worst Makers (Jenny DeVito)]
  GitHub: https://github.com/worstmakers/carronho

  REFERENCES:
  https://github.com/d03n3rfr1tz3/HC-SR04
  https://www.utmel.com/components/l9110s-2-channel-motor-driver-circuit-pinout-and-how-to-work-video-faq?id=1988

  WIRING (All GND were connected on the same pin - same breadboard column -
  SAME UNO GND) Red LED:
    NEG = GND - breadboard
    D2 = 220R RESISTOR = +POLE RED LED
  HC-SR04:
    Trig = D13
    Echo = D12
    VCC = 5V
    GND = GND - breadboard
  L9110S H-Bridge:
    OA1 = GEAR 1
    OB1 = GEAR 1
    OA2 = GEAR 2
    OB2 = GEAR 2
    VCC = RED WIRE BATTERIES HOLDER
    GND = GND - breadboard
    A-1B = D5(PWM)
    A-1A = D6(PWM)
    B-1A = D10(PWM)
    B-1B = D9(PWM)

  CIRCUIT
  The gears are powered by 4xAA bateries and the UNO is powered by a 9V
  battery GND are commom to the circuit and the red LED is wired with a 220R
  resistor in series.
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

  HCSR04.measureMicroseconds(times);
  /*
    for (int i = 0; i < echoCount; i++) {
      if (i > 0) Serial.print(" | ");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(times[i]);
      Serial.print(" μs");
    }

    Serial.println("");
    */
  delay(100);

  HCSR04.measureDistanceCm(distances);
  int i = 0;
  // for (int i = 0; i < echoCount; i++) {
  // if (i > 0) Serial.print(" | ");
  // Serial.print(i + 1);
  // Serial.print(": ");
  Serial.print(distances[i]);
  Serial.println(" cm");

  if (distances[i] > 0 && distances[i] <= 3) {
    digitalWrite(redLED, HIGH);
    stop();
    delay(1000);
    backward();
    delay(500);
    backward();
  } else if ((distances[i] > 3) && (distances[i] <= 10)) {
    direction = random(1, 101);
    if (direction % 2 == 0) {
      backright();
      digitalWrite(redLED, LOW);
      delay(300);
      backward();
      digitalWrite(redLED, HIGH);
      delay(150);
      backright();
      digitalWrite(redLED, LOW);
      delay(300);
    } else {
      backleft();
      digitalWrite(redLED, LOW);
      delay(300);
      backward();
      digitalWrite(redLED, HIGH);
      delay(150);
      backleft();
      digitalWrite(redLED, LOW);
      delay(300);
    }
  } else {
    digitalWrite(redLED, LOW);
    Serial.println("");
    forward();
  }
  //}

  Serial.println("");
  delay(100);
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
