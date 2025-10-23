#ifndef TRAIT_BOW_H
#define TRAIT_BOW_H

#include <Arduino.h>
#include "../poses/pose_composites.h"

// 🐾 Trait: Bow
void trait_bow() {
  Serial.println("Trait: Bow");

  poseBow();         // Lower front legs, keep rear upright
  delay(1000);       // Hold the bow for 1 seconds
  poseStand();       // Return to standing posture
}

#endif