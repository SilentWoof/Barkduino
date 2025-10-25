#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include <Arduino.h>
#include "../utils/servo_utils.h"
#include "../poses/pose_composites.h"

// 🦿 Waggle a leg using its manual wrapper
void waggleManual(void (*legFunc)(int, int), const char* label, int centerAngle = 90, int durationMs = 3000) {
  Serial.print("Waggling "); Serial.println(label);

  for (unsigned long t = millis(); millis() - t < durationMs;) {
    legFunc(centerAngle - 20, 300);
    legFunc(centerAngle + 20, 300);
  }

  legFunc(centerAngle, 500);
}

// 🛠️ Mode 4: Waggle test dispatcher
void runWaggleTest(bool loop = true) {
  Serial.println("Mode 4 — Waggle Test");
  poseStand();

  do {
    waggleManual(frontLeftManual,  "Front Left");
    waggleManual(frontRightManual, "Front Right");
    waggleManual(rearLeftManual,   "Rear Left");
    waggleManual(rearRightManual,  "Rear Right");
  } while (loop);

  Serial.println("Waggle test complete.");
}

#endif