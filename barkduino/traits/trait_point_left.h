#ifndef TRAIT_POINT_LEFT_H
#define TRAIT_POINT_LEFT_H

#include <Arduino.h>
#include "../poses/pose_composites.h"
#include "../utils/motion_speed_presets.h"  // ✅ Speed + step size presets

// 🐾 trait_point_left.h
//
// This trait performs an expressive "point left" gesture using Barkduino's composite pose system.
//
// ✅ Purpose:
// - Demonstrates an asymmetrical front-leg extension to the left
// - Uses a crouched rear stance for balance and expressiveness
// - Holds the pose briefly, then returns to a neutral standing posture
//
// ✅ Functionality:
// - Calls `posePointLeft()` with SPEED_STANDARD and STEP_STANDARD for consistent timing
// - Uses a randomized delay to simulate natural hold duration
// - Returns to `poseStand()` for reset
//
// ✅ Usage:
//     trait_point_left();  // Executes the full point-left gesture sequence

void trait_point_left() {
  Serial.println("Trait: Point Left");

  delay(500);  // Wait for 0.5 seconds before starting

  posePointLeft(SPEED_STANDARD, STEP_STANDARD);  // Asymmetric front leg pose with crouched rear
  delay(random(1000, 3001));                     // Hold the point for 1 to 3 seconds
  poseStand(SPEED_STANDARD, STEP_STANDARD);      // Return to standing posture
}

#endif