#ifndef TRAIT_BOW_H
#define TRAIT_BOW_H

#include <Arduino.h>
#include "../poses/leg_primitives.h"
#include "../utils/motion_speed_presets.h"  // ✅ Speed + step size presets

void trait_bow() {
  Serial.println("Trait: Bow");

  delay(1000);
  RearStraight(SPEED_STANDARD, STEP_STANDARD);     // 🐢 Smooth rear leg sweep
  FrontBack(SPEED_DEAD_SLOW, STEP_STANDARD);        // 🐢 Smooth front fold
  delay(2000);
  FrontStraight(SPEED_DEAD_SLOW, STEP_STANDARD);    // 🐢 Return to straight
  delay(250);
  RearForward(SPEED_STANDARD, STEP_STANDARD);      // 🐢 Final rear fold
  delay(1000);
}

#endif