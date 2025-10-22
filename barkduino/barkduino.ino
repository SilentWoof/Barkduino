#include <Servo.h>
#include "traits/trait_wait.h"
#include "poses/leg_primitives.h"
#include "poses/pose_composites.h"

// Servo objects
Servo front_left;
Servo front_right;
Servo rear_left;
Servo rear_right;

// Servo pins
const int pin_front_left  = 11;
const int pin_front_right = 10;
const int pin_rear_left   = 12;
const int pin_rear_right  = 9;

// Distance sensor pins
const int trigPin = 4;
const int echoPin = 5;

// Mode selection
const int MODE_PRODUCTION   = 1;
const int MODE_TRAIT_TEST   = 2;
const int MODE_CALIBRATION  = 3;
const int MODE_WAGGLE_TEST  = 4;
const int ACTIVE_MODE       = MODE_PRODUCTION;

const int SELECTED_TRAIT = 0;  // Index in traitRegistry[]

// Trait registry
typedef void (*TraitFunction)();
TraitFunction traitRegistry[] = {
  trait_wait,
  // Add future traits here like trait_wave, trait_bow, etc.
};

void setup() {
  Serial.begin(9600);
  Serial.println("=== Robot Startup ===");
  Serial.println("Initializing servos...");
  front_left.attach(pin_front_left);
  front_right.attach(pin_front_right);
  rear_left.attach(pin_rear_left);
  rear_right.attach(pin_rear_right);

  Serial.println("Initializing distance sensor...");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  delay(100);

  Serial.print("Active mode: ");
  if (ACTIVE_MODE == MODE_PRODUCTION) Serial.println("Production");
  else if (ACTIVE_MODE == MODE_TRAIT_TEST) Serial.println("Trait Testing");
  else if (ACTIVE_MODE == MODE_CALIBRATION) Serial.println("Calibration");
  else if (ACTIVE_MODE == MODE_WAGGLE_TEST) Serial.println("Waggle Test");
  else Serial.println("Unknown");

  if (ACTIVE_MODE != MODE_WAGGLE_TEST) {
    Serial.println("Setting initial pose: Sleeping");
    poseSleeping();
  }
}

void loop() {
  switch (ACTIVE_MODE) {
    case MODE_PRODUCTION:
      runProductionLoop();
      break;
    case MODE_TRAIT_TEST:
      runTraitTestingLoop();
      break;
    case MODE_CALIBRATION:
      runCalibrationMode();
      break;
    case MODE_WAGGLE_TEST:
      runWaggleTest();
      break;
    default:
      Serial.println("Invalid mode selected.");
      break;
  }
}

// 🔧 Distance Sensor
long getDistanceCM() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  long distance = duration * 0.034 / 2;
  return distance;
}

bool isTriggerDetected() {
  long distance = getDistanceCM();
  Serial.print("Sensor reading: ");
  Serial.print(distance);
  Serial.println(" cm");
  return (distance > 0 && distance < 20);
}

// 🔧 Synchronized Sweep Function
void sweepPair(Servo& s1, int start1, int end1,
               Servo& s2, int start2, int end2,
               int duration_ms) {
  Serial.print("Sweeping pair from ");
  Serial.print(start1); Serial.print("/"); Serial.print(start2);
  Serial.print(" to ");
  Serial.print(end1); Serial.print("/"); Serial.print(end2);
  Serial.print(" over "); Serial.print(duration_ms); Serial.println("ms");

  const int steps = 20;
  for (int i = 0; i <= steps; i++) {
    float t = (float)i / steps;
    int pos1 = start1 + (end1 - start1) * t;
    int pos2 = start2 + (end2 - start2) * t;
    s1.write(pos1);
    s2.write(pos2);
    delay(duration_ms / steps);
  }
}

// 🔧 Synchronization Wrappers
void syncRearLegs(int leftTarget, int rightTarget, int duration = 500) {
  Serial.println("Syncing rear legs...");
  int leftStart = rear_left.read();
  int rightStart = rear_right.read();
  sweepPair(rear_left, leftStart, leftTarget, rear_right, rightStart, rightTarget, duration);
}

void syncFrontLegs(int leftTarget, int rightTarget, int duration = 500) {
  Serial.println("Syncing front legs...");
  int leftStart = front_left.read();
  int rightStart = front_right.read();
  sweepPair(front_left, leftStart, leftTarget, front_right, rightStart, rightTarget, duration);
}

// 🚦 Mode Loops
void runProductionLoop() {
  if (isTriggerDetected()) {
    Serial.println("Production Mode: Trigger detected.");

    poseSleeping();
    delay(500);

    poseStanding();
    delay(500);

    int traitCount = sizeof(traitRegistry) / sizeof(traitRegistry[0]);
    int selected = random(traitCount);
    Serial.print("Production Mode: Selected trait ID ");
    Serial.println(selected);
    traitRegistry[selected]();

    delay(500);

    Serial.println("Returning to sleep...");
    poseSleeping();
    Serial.println("Cycle complete. Awaiting next trigger...");
    delay(1000);
  }
}

void runTraitTestingLoop() {
  if (isTriggerDetected()) {
    Serial.println("Trait Testing Mode: Trigger detected.");

    poseSleeping();
    delay(500);

    poseStanding();
    delay(500);

    int traitCount = sizeof(traitRegistry) / sizeof(traitRegistry[0]);
    if (SELECTED_TRAIT >= 0 && SELECTED_TRAIT < traitCount) {
      Serial.print("Trait Testing Mode: Selected trait ID ");
      Serial.println(SELECTED_TRAIT);
      traitRegistry[SELECTED_TRAIT]();
    } else {
      Serial.println("Trait Testing Mode: Invalid trait ID.");
    }

    delay(500);

    Serial.println("Returning to sleep...");
    poseSleeping();
    Serial.println("Cycle complete. Awaiting next trigger...");
    delay(1000);
  }
}

void runCalibrationMode() {
  Serial.println("Mode: Servo Calibration");
  poseStanding();
}

void runWaggleTest() {
  Serial.println("Mode: Waggle Test");
  poseStanding();

  waggleLeg(front_left, "Front Left");
  waggleLeg(front_right, "Front Right");
  waggleLeg(rear_left, "Rear Left");
  waggleLeg(rear_right, "Rear Right");

  Serial.println("Waggle test complete.");
  while (true);
}

void waggleLeg(Servo& leg, const char* label) {
  Serial.print("Waggling "); Serial.println(label);
  int center = leg.read();
  int offset = 20;
  unsigned long startTime = millis();
  while (millis() - startTime < 3000) {
    leg.write(center - offset);
    delay(300);
    leg.write(center + offset);
    delay(300);
  }
  leg.write(center);
  delay(500);
}