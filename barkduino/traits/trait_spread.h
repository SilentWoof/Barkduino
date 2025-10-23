#ifndef TRAIT_SPREAD_H
#define TRAIT_SPREAD_H

#include <Arduino.h>
#include "../poses/pose_composites.h"

// 🐾 Trait: Spread
void trait_spread() {
  Serial.println("Trait: Spread");

  poseSpread();       // Stretch front legs forward, rear legs back
  delay(3000);        // Hold the stretch for 3 seconds
  poseStand();        // Return to standing posture
}

#endif