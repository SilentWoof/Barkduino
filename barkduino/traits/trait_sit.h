#ifndef TRAIT_SIT_H
#define TRAIT_SIT_H

#include <Arduino.h>
#include "../poses/pose_composites.h"

// 🐾 Trait: Sit
void trait_sit() {
  Serial.println("Trait: Sit");

  poseSit();         // Call static sit pose
  delay(3000);       // Hold for 5 seconds
  poseStand();       // Return to standing pose
}

#endif