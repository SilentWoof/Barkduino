#ifndef TRAIT_SPREAD_H
#define TRAIT_SPREAD_H

#include <Arduino.h>
#include "../poses/pose_composites.h"

// 🐾 Trait: Spread
void trait_spread() {
  const int medium = 10;

  Serial.println("Trait: Spread");

  poseSpread(medium);       // Stretch front legs forward, rear legs back
  delay(3000);              // Hold the stretch for 3 seconds
  poseStand(medium);        // Return to standing posture
}

#endif