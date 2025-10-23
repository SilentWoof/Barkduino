#ifndef TRAIT_POINT_H
#define TRAIT_POINT_H

#include <Arduino.h>
#include "../poses/pose_composites.h"

// 🐾 Trait: Point
void trait_point() {
  Serial.println("Trait: Point");

  posePoint();        // Asymmetric front leg pose with crouched rear
  delay(3000);        // Hold the point for 3 seconds
  poseStand();        // Return to standing posture
}

#endif