#ifndef TRAIT_POUNCE_H
#define TRAIT_POUNCE_H

#include <Arduino.h>
#include "../poses/pose_composites.h"
#include "../poses/leg_primitives.h"  // Needed for FrontStraight()
#include "../configs/motion_config.h"  // Optional if timing constants are reused

// 🐾 Trait: Pounce
void trait_pounce() {
  Serial.println("Trait: Pounce");

  posePounce();        // Crouch with rear legs midway back, front legs forward
  delay(750);          // Initial hold
  FrontStraight();     // Extend front legs
  delay(random(100, 1001));
  posePounce();        // Return to pounce
  delay(random(100, 3001));
  FrontStraight();     // Extend again
  delay(random(100, 1001));
  posePounce();        // Return again
  delay(random(100, 3001));
  poseStand();         // Final stand
}

#endif