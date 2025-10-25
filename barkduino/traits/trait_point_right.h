#ifndef TRAIT_POINT_RIGHT_H
#define TRAIT_POINT_RIGHT_H

#include <Arduino.h>
#include "../poses/pose_composites.h"

// 🐾 Trait: Point Right
void trait_point_right() {
  const int slow = 40;  // Slower movement speed

  Serial.println("Trait: Point Right");
  delay(500);                           // Wait for 0.5 seconds before starting
  posePointRight(slow);                // Asymmetric front leg pose with crouched rear
  delay(random(1000, 3001));           // Hold the point for 1 to 3 seconds
  poseStand(slow);                     // Return to standing posture
}

#endif