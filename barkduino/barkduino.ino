#include <Servo.h>
#include "configs/motion_config.h"  // ⏱️ Centralized motion timing
#include "poses/leg_primitives.h"
#include "poses/pose_composites.h"
#include "traits/trait_bow.h"
#include "traits/trait_point.h"
#include "traits/trait_pounce.h"
#include "traits/trait_sit.h"
#include "traits/trait_spread.h"
#include "traits/trait_wait.h"

// 🦴 Servo objects for each leg
Servo front_left;
Servo front_right;
Servo rear_left;
Servo rear_right;

// 🧩 Servo pin assignments
const int pin_front_left  = 9;
const int pin_front_right = 10;
const int pin_rear_left   = 11;
const int pin_rear_right  = 12;

// 📡 Distance sensor pins
const int echoPin = 4;
const int trigPin = 5;

// 🚦 Mode Constants
const int MODE_1 = 1;  // Production Mode: Triggered loop with random trait
const int MODE_2 = 2;  // Trait Testing Mode: Triggered loop with selected trait
const int MODE_3 = 3;  // Calibration Mode: Static standing pose for tuning
const int MODE_4 = 4;  // Waggle Test Mode: Cycles each leg for servo check

const int ACTIVE_MODE = MODE_1;  // Set active mode here
const int SELECTED_TRAIT = 0;    // Index in traitRegistry[]

// 🧠 Trait registry for modular behavior selection
typedef void (*TraitFunction)();
TraitFunction traitRegistry[] = {
  trait_bow,        // Index 0
  trait_point,      // Index 1
  trait_pounce,     // Index 2
  trait_sit,        // Index 3
  trait_spread,     // Index 4
  trait_wait        // Index 5
};

// 🛠️ Setup: Initialize servos, sensor, and pose
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
  if (ACTIVE_MODE == MODE_1) Serial.println("Mode 1 — Production");
  else if (ACTIVE_MODE == MODE_2) Serial.println("Mode 2 — Trait Testing");
  else if (ACTIVE_MODE == MODE_3) Serial.println("Mode 3 — Calibration");
  else if (ACTIVE_MODE == MODE_4) Serial.println("Mode 4 — Waggle Test");
  else Serial.println("Unknown");

  if (ACTIVE_MODE != MODE_4) {
    Serial.println("Setting initial pose: Sleep");
    poseSleep();
  }
}

// 🔁 Main loop: Dispatches to selected mode
void loop() {
  switch (ACTIVE_MODE) {
    case MODE_1:
      runProductionLoop();  // Random trait on trigger
      break;
    case MODE_2:
      runTraitTestingLoop();  // Selected trait on trigger
      break;
    case MODE_3:
      runCalibrationMode();  // Static pose for tuning
      break;
    case MODE_4:
      runWaggleTest();  // Servo identification test
      break;
    default:
      Serial.println("Invalid mode selected.");
      break;
  }
}

// 📏 Measure distance from ultrasonic sensor
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

// 🚨 Trigger detection based on proximity
bool isTriggerDetected() {
  long distance = getDistanceCM();
  Serial.print("Sensor reading: ");
  Serial.print(distance);
  Serial.println(" cm");
  return (distance > 0 && distance < 20);
}

// 🔧 Sweep two servos in sync over a duration
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

// 🔧 Rear leg synchronization wrapper
void syncRearLegs(int leftTarget, int rightTarget, int duration = DEFAULT_SYNC_DURATION) {
  Serial.println("Syncing rear legs...");
  int leftStart = rear_left.read();
  int rightStart = rear_right.read();
  sweepPair(rear_left, leftStart, leftTarget, rear_right, rightStart, rightTarget, duration);
}

// 🔧 Front leg synchronization wrapper
void syncFrontLegs(int leftTarget, int rightTarget, int duration = DEFAULT_SYNC_DURATION) {
  Serial.println("Syncing front legs...");
  int leftStart = front_left.read();
  int rightStart = front_right.read();
  sweepPair(front_left, leftStart, leftTarget, front_right, rightStart, rightTarget, duration);
}

// 🎭 Mode 1: Random trait execution on trigger
void runProductionLoop() {
  if (isTriggerDetected()) {
    Serial.println("Mode 1 — Production: Trigger detected.");

    poseStand();
    delay(250);

    int traitCount = sizeof(traitRegistry) / sizeof(traitRegistry[0]);
    int selected = random(traitCount);
    Serial.print("Mode 1 — Production: Selected trait ID ");
    Serial.println(selected);
    traitRegistry[selected]();

    delay(250);

    Serial.println("Returning to sleep...");
    poseSleep();
    Serial.println("Cycle complete. Awaiting next trigger...");
  }
}

// 🎭 Mode 2: Selected trait execution on trigger
void runTraitTestingLoop() {
  if (isTriggerDetected()) {
    Serial.println("Mode 2 — Trait Testing: Trigger detected.");

    poseStand();

    int traitCount = sizeof(traitRegistry) / sizeof(traitRegistry[0]);
    if (SELECTED_TRAIT >= 0 && SELECTED_TRAIT < traitCount) {
      Serial.print("Mode 2 — Trait Testing: Selected trait ID ");
      Serial.println(SELECTED_TRAIT);
      traitRegistry[SELECTED_TRAIT]();
    } else {
      Serial.println("Mode 2 — Trait Testing: Invalid trait ID.");
    }

    Serial.println("Returning to sleep...");
    poseSleep();
    Serial.println("Cycle complete. Awaiting next trigger...");
  }
}

// 🛠️ Mode 3: Static standing pose for calibration
void runCalibrationMode() {
  Serial.println("Mode 3 — Servo Calibration");
  poseStand();
}

// 🛠️ Mode 4: Waggle test for servo identification
void runWaggleTest() {
  Serial.println("Mode 4 — Waggle Test");
  poseStand();

  waggleLeg(front_left, "Front Left");
  waggleLeg(front_right, "Front Right");
  waggleLeg(rear_left, "Rear Left");
  waggleLeg(rear_right, "Rear Right");

  Serial.println("Waggle test complete.");
  while (true);  // Halt after test
}

// 🦿 Waggle a single leg for identification
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
