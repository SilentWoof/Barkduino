#ifndef TRAIT_SIT_H
#define TRAIT_SIT_H

#include <Arduino.h>
#include "../poses/pose_composites.h"

// 🐾 Trait: Sit
void trait_sit() {
  const int medium = 25;  // Medium movement speed

  Serial.println("Trait: Sit");

  poseSit(medium);         // Call static sit pose
  delay(5000);             // Hold for 5 seconds
  poseStand(medium);       // Return to standing pose
}

#endif