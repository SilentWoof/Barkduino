#include <Servo.h>
#include "configs/motion_config.h"
#include "poses/leg_primitives.h"
#include "poses/pose_composites.h"
#include "traits/trait_registry.h"
#include "utils/trait_executor.h"
#include "utils/trigger_logic.h"
#include "utils/servo_utils.h"
#include "utils/diagnostics.h"
#include "modes/mode_production.h"
#include "modes/mode_trait_test.h"
#include "modes/mode_calibration.h"

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

// 🚦 Mode Constants
const int MODE_1 = 1;
const int MODE_2 = 2;
const int MODE_3 = 3;
const int MODE_4 = 4;

const int ACTIVE_MODE = MODE_1;
const int SELECTED_TRAIT = 1;     // Used in MODE_2

int lastTraitIndex = -1;  // Prevents immediate trait repetition in Mode 1

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