#ifndef POSE_COMPOSITES_H
#define POSE_COMPOSITES_H

#include <Arduino.h>
#include "leg_primitives.h"

// 🎭 Composite Poses

void poseSleeping() {
  Serial.println("Pose: Sleeping");
  rearLegsFoldedForward();
  delay(500);
  frontLegsFoldedBack();
}

void poseStanding() {
  Serial.println("Pose: Standing");
  frontLegsStraight();
  delay(500);
  rearLegsStraight();
}

#endif