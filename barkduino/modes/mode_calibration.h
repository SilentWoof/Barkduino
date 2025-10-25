#ifndef MODE_CALIBRATION_H
#define MODE_CALIBRATION_H

#include <Arduino.h>
#include "../poses/pose_composites.h"

// 🛠️ Mode 3: Servo calibration pose
void runCalibrationMode() {
  Serial.println("Mode 3 — Servo Calibration");
  poseStand();
}

#endif