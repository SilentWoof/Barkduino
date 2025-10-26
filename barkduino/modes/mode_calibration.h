#ifndef MODE_CALIBRATION_H
#define MODE_CALIBRATION_H

#include <Arduino.h>
#include "../utils/motion_config.h"
#include "../utils/servo_utils.h"      // ✅ Centralized servo control
#include "../poses/leg_primitives.h"   // ✅ Leg primitives: FrontStraight, RearStraight

// 🛠️ Mode 3: Servo calibration pose
void runCalibrationMode() {
  Serial.println("Mode 3 — Servo Calibration");
  Serial.print("Setting all servos to straight using primitives at ");
  Serial.print(DEFAULT_SYNC_DURATION); Serial.println("ms...");

  // ✅ Use modular leg primitives with configured speed
  FrontStraight(DEFAULT_SYNC_DURATION);
  RearStraight(DEFAULT_SYNC_DURATION);

  delay(250);  // Let servos settle

  // 🧪 Diagnostic readout
  Serial.println("✅ All servos swept to straight pose via primitives");
  Serial.print("Front Left (raw): ");  Serial.println(front_left.read());
  Serial.print("Front Right: ");       Serial.println(front_right.read());
  Serial.print("Rear Left (raw): ");   Serial.println(rear_left.read());
  Serial.print("Rear Right: ");        Serial.println(rear_right.read());
}

#endif