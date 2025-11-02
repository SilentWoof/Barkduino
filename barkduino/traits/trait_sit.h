#ifndef TRAIT_SIT_H
#define TRAIT_SIT_H

#include <Arduino.h>
#include "../poses/pose_composites.h"
#include "../utils/motion_speed_presets.h"  // ✅ Speed + step size presets

// 🐾 trait_sit.h
//
// This trait performs a static "sit" gesture using Barkduino's composite pose system.
//
// ✅ Purpose:
// - Demonstrates a seated posture with rear legs forward and front legs straight
// - Holds the pose for a fixed duration to simulate rest or attention
// - Returns to a neutral standing posture
//
// ✅ Functionality:
// - Calls `poseSit()` and `poseStand()` with SPEED_STANDARD and STEP_STANDARD
// - Uses a fixed 5-second delay to hold the seated position
//
// ✅ Usage:
//     trait_sit();  // Executes the full sit-and-stand sequence

void trait_sit() {
  Serial.println("Trait: Sit");

  poseSit(SPEED_STANDARD, STEP_STANDARD);     // Call static sit pose
  delay(random(3000, 7001));                   // Sit for between 3 and 5 seconds
  poseStand(SPEED_STANDARD, STEP_STANDARD);   // Return to standing pose
}

#endif