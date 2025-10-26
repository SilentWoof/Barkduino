#ifndef TRAIT_POUNCE_H
#define TRAIT_POUNCE_H

#include <Arduino.h>
#include "../poses/pose_composites.h"
#include "../poses/leg_primitives.h"
#include "../utils/motion_config.h"  // Optional if timing constants are reused

// 🐾 Trait: Pounce
void trait_pounce() {
  const int fast = 10;

  Serial.println("Trait: Pounce");

  posePounce(fast);         // Crouch with rear legs midway back, front legs forward
  delay(750);               // Initial hold
  FrontStraight(fast);      // Extend front legs
  delay(random(100, 1001));
  posePounce(fast);         // Return to pounce
  delay(random(100, 3001));
  FrontStraight(fast);      // Extend again
  delay(random(100, 1001));
  posePounce(fast);         // Return again
  delay(random(100, 3001));
  poseStand(fast);          // Final stand
}

#endif