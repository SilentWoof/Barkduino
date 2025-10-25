#ifndef TRAIT_POINT_LEFT_H
#define TRAIT_POINT_LEFT_H

#include <Arduino.h>
#include "../poses/pose_composites.h"

// 🐾 Trait: Point Left
void trait_point_left() {
  Serial.println("Trait: Point Left");
  delay(500);                           // Wait for 0.5 seconds before starting
  posePointLeft();                      // Asymmetric front leg pose with crouched rear
  delay(random(1000, 3001));            // Hold the point for 1 to 3 seconds
  poseStand();                          // Return to standing posture
}

#endif