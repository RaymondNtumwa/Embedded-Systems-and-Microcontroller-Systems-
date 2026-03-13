#include <Servo.h>

// --- Create 4 servo objects ---
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// --- Servo pins ---
const int SERVO1_PIN = 3;
const int SERVO2_PIN = 5;
const int SERVO3_PIN = 6;
const int SERVO4_PIN = 9;

// --- Potentiometer pins (analog) ---
const int POT1_PIN = A0;
const int POT2_PIN = A1;
const int POT3_PIN = A2;
const int POT4_PIN = A3;

void setup() {
  // Attach each servo to its pin
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo3.attach(SERVO3_PIN);
  servo4.attach(SERVO4_PIN);

  Serial.begin(9600);
  Serial.println("4-Servo Control Ready");
}

void loop() {
  // --- Read each potentiometer (0 - 1023) ---
  int pot1Val = analogRead(POT1_PIN);
  int pot2Val = analogRead(POT2_PIN);
  int pot3Val = analogRead(POT3_PIN);
  int pot4Val = analogRead(POT4_PIN);

  // --- Map pot values (0-1023) to servo angle (0-180) ---
  int angle1 = map(pot1Val, 0, 1023, 0, 180);
  int angle2 = map(pot2Val, 0, 1023, 0, 180);
  int angle3 = map(pot3Val, 0, 1023, 0, 180);
  int angle4 = map(pot4Val, 0, 1023, 0, 180);

  // --- Write angles to each servo ---
  servo1.write(angle1);
  servo2.write(angle2);
  servo3.write(angle3);
  servo4.write(angle4);

  // --- Print angles to Serial Monitor for debugging ---
  Serial.print("S1: "); Serial.print(angle1);
  Serial.print(" | S2: "); Serial.print(angle2);
  Serial.print(" | S3: "); Serial.print(angle3);
  Serial.print(" | S4: "); Serial.println(angle4);

  delay(20); // Small delay for stability
}
