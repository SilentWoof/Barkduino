#include <Servo.h>
#include "configs/motion_config.h"
#include "poses/leg_primitives.h"
#include "poses/pose_composites.h"
#include "traits/trait_bow.h"
#include "traits/trait_point_left.h"
#include "traits/trait_point_right.h"
#include "traits/trait_pounce.h"
#include "traits/trait_sit.h"
#include "traits/trait_spread.h"
#include "traits/trait_wait.h"

// 🦴 Servo objects
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
const int MODE_1 = 1;
const int MODE_2 = 2;
const int MODE_3 = 3;
const int MODE_4 = 4;

const int ACTIVE_MODE = MODE_2;
const int SELECTED_TRAIT = 0;  // Used in MODE_2

// 🧠 Trait registry
typedef void (*TraitFunction)();
TraitFunction traitRegistry[] = {
  trait_bow,         // 0
  trait_point_left,  // 1
  trait_point_right, // 2
  trait_pounce,      // 3
  trait_sit,         // 4
  trait_spread,      // 5
  trait_wait         // 6
};

// 🕒 Trigger control
unsigned long lastTriggerTime = 0;
const unsigned long triggerCooldown = 3000;
bool triggerLocked = false;
bool traitInProgress = false;

void setup() {
  Serial.begin(9600);
  Serial.println("=== Robot Startup ===");

  front_left.attach(pin_front_left);
  front_right.attach(pin_front_right);
  rear_left.attach(pin_rear_left);
  rear_right.attach(pin_rear_right);

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

void loop() {
  switch (ACTIVE_MODE) {
    case MODE_1: runProductionLoop(); break;
    case MODE_2: runTraitTestingLoop(); break;
    case MODE_3: runCalibrationMode(); break;
    case MODE_4: runWaggleTest(); break;
    default: Serial.println("Invalid mode selected."); break;
  }
}

// 📏 Distance measurement
long getDistanceCM() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  return duration * 0.034 / 2;
}

// 🚨 Unified trigger detection
bool isTriggerDetected() {
  long distance = getDistanceCM();
  unsigned long now = millis();

  if (distance > 0 && distance < 20) {
    if (!triggerLocked && !traitInProgress) {
      lastTriggerTime = now;
      triggerLocked = true;
      Serial.print("Sensor reading: ");
      Serial.print(distance);
      Serial.println(" cm — Trigger accepted");
      return true;
    }
  } else {
    if (triggerLocked) Serial.println("Sensor clear — trigger unlocked");
    triggerLocked = false;
  }

  return false;
}

// 🧠 Trait execution wrapper
void executeTrait(TraitFunction trait) {
  traitInProgress = true;
  trait();  // Run the trait
  poseSleep();  // Return to sleep posture
  Serial.println("Trait complete. Enforcing cooldown...");
  delay(triggerCooldown);  // Force cooldown delay
  traitInProgress = false;
  triggerLocked = false;   // Require sensor to clear before next trigger
}

// 🔧 Servo sweep
void sweepPair(Servo& s1, int start1, int end1,
               Servo& s2, int start2, int end2,
               int duration_ms) {
  const int steps = 20;
  for (int i = 0; i <= steps; i++) {
    float t = (float)i / steps;
    s1.write(start1 + (end1 - start1) * t);
    s2.write(start2 + (end2 - start2) * t);
    delay(duration_ms / steps);
  }
}

// 🔧 Sync wrappers
void syncRearLegs(int leftTarget, int rightTarget, int duration = DEFAULT_SYNC_DURATION) {
  sweepPair(rear_left, rear_left.read(), leftTarget, rear_right, rear_right.read(), rightTarget, duration);
}

void syncFrontLegs(int leftTarget, int rightTarget, int duration = DEFAULT_SYNC_DURATION) {
  sweepPair(front_left, front_left.read(), leftTarget, front_right, front_right.read(), rightTarget, duration);
}

// 🎭 Mode 1: Random trait
void runProductionLoop() {
  if (traitInProgress) return;

  if (isTriggerDetected()) {
    Serial.println("Mode 1 — Production: Trigger detected.");
    poseStand(); delay(250);

    int selected = random(sizeof(traitRegistry) / sizeof(traitRegistry[0]));
    Serial.print("Selected trait ID "); Serial.println(selected);
    executeTrait(traitRegistry[selected]);
  }
}

// 🎭 Mode 2: Selected trait
void runTraitTestingLoop() {
  if (traitInProgress) return;

  if (isTriggerDetected()) {
    Serial.println("Mode 2 — Trait Testing: Trigger detected.");
    poseStand();

    int traitCount = sizeof(traitRegistry) / sizeof(traitRegistry[0]);
    if (SELECTED_TRAIT >= 0 && SELECTED_TRAIT < traitCount) {
      Serial.print("Selected trait ID "); Serial.println(SELECTED_TRAIT);
      executeTrait(traitRegistry[SELECTED_TRAIT]);
    } else {
      Serial.println("Invalid trait ID.");
    }
  }
}

// 🛠️ Mode 3: Calibration
void runCalibrationMode() {
  Serial.println("Mode 3 — Servo Calibration");
  poseStand();
}

// 🛠️ Mode 4: Waggle test
void runWaggleTest() {
  Serial.println("Mode 4 — Waggle Test");
  poseStand();

  waggleLeg(front_left, "Front Left");
  waggleLeg(front_right, "Front Right");
  waggleLeg(rear_left, "Rear Left");
  waggleLeg(rear_right, "Rear Right");

  Serial.println("Waggle test complete.");
  while (true);
}

// 🦿 Waggle a leg
void waggleLeg(Servo& leg, const char* label) {
  Serial.print("Waggling "); Serial.println(label);
  int center = leg.read();
  for (unsigned long t = millis(); millis() - t < 3000;) {
    leg.write(center - 20); delay(300);
    leg.write(center + 20); delay(300);
  }
  leg.write(center); delay(500);
}