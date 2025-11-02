#ifndef TRAIT_SPREAD_H
#define TRAIT_SPREAD_H

#include <Arduino.h>
#include "../poses/pose_composites.h"
#include "../utils/motion_speed_presets.h"  // ✅ Speed + step size presets

// 🐾 trait_spread.h
//
// This trait performs a full-body "spread" gesture using Barkduino's composite pose system.
//
// ✅ Purpose:
// - Demonstrates a stretched posture with front legs extended forward and rear legs pushed back
// - Simulates a relaxed or dramatic stretch
// - Returns to a neutral standing posture after holding
//
// ✅ Functionality:
// - Calls `poseSpread()` and `poseStand()` with SPEED_STANDARD and STEP_STANDARD
// - Holds the spread pose for 3 seconds before reset
//
// ✅ Usage:
//     trait_spread();  // Executes the full spread-and-stand sequence

void trait_spread() {
  Serial.println("Trait: Spread");
  
  delay(1000);                                    // Brief pause before spreading
  poseSpread(SPEED_STANDARD, STEP_STANDARD);      // Stretch front legs forward, rear legs back
  delay(random(1000, 5001));                      // Hold the stretch for 1 to 5 seconds
  poseStand(SPEED_STANDARD, STEP_STANDARD);       // Return to standing posture
  delay(1000);                                    // Brief pause after standing
}

#endif