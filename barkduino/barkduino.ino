#include <Servo.h>

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

const int SELECTED_TRAIT = 1;  // 1 = Wait

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
      break;
    case MODE_WAGGLE_TEST:
      runWaggleTest();
      break;
    default:
      Serial.println("Invalid mode selected.");
      break;
  }
}

//
// 🔧 Distance Sensor
//
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

//
// 🔧 Synchronized Sweep Function
//
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

//
// 🔧 Synchronization Wrappers
//
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

//
// 🧩 Primitive Leg Positions
//
void rearLegsFoldedForward() {
  Serial.println("Rear legs: folded forward");
  syncRearLegs(0, 180);
}

void rearLegsStraight() {
  Serial.println("Rear legs: straight");
  syncRearLegs(100, 60);
}

void frontLegsFoldedBack() {
  Serial.println("Front legs: folded back");
  syncFrontLegs(160, 20);
}

void frontLegsStraight() {
  Serial.println("Front legs: straight");
  syncFrontLegs(60, 110);
}

//
// 🎭 Composite Poses
//
void poseSleeping() {
  Serial.println("Pose: Sleeping");
  rearLegsFoldedForward();
  delay(500);
  frontLegsFoldedBack();
}

void poseStanding() {
  Serial.println("Pose: Standing");
  frontLegsStraight();
  delay(500);
  rearLegsStraight();
}

//
// 🎬 Traits
//
void performTrait(int traitID) {
  Serial.print("Executing trait ID: ");
  Serial.println(traitID);
  switch (traitID) {
    case 1:
      Serial.println("Trait: Wait");
      delay(2000);
      break;
    default:
      Serial.println("Unknown trait.");
      break;
  }
}

//
// 🚦 Mode Loops
//
void runProductionLoop() {
  if (isTriggerDetected()) {
    Serial.println("Production Mode: Trigger detected.");

    poseSleeping();
    delay(500);

    poseStanding();
    delay(500);

    performTrait(1);  // Only trait: wait
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

    performTrait(SELECTED_TRAIT);  // Should be 1 for "wait"
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
