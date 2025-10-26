#ifndef TRAIT_POINT_RIGHT_H
#define TRAIT_POINT_RIGHT_H

#include <Arduino.h>
#include "../poses/pose_composites.h"
#include "../utils/motion_speed_presets.h"  // ✅ Speed + step size presets

// 🐾 trait_point_right.h
//
// This trait performs an expressive "point right" gesture using Barkduino's composite pose system.
//
// ✅ Purpose:
// - Demonstrates an asymmetrical front-leg extension to the right
// - Uses a crouched rear stance for balance and expressiveness
// - Holds the pose briefly, then returns to a neutral standing posture
//
// ✅ Functionality:
// - Calls `posePointRight()` with SPEED_STANDARD and STEP_STANDARD for consistent timing
// - Uses a randomized delay to simulate natural hold duration
// - Returns to `poseStand()` for reset
//
// ✅ Usage:
//     trait_point_right();  // Executes the full point-right gesture sequence

void trait_point_right() {
  Serial.println("Trait: Point Right");

  delay(500);  // Wait for 0.5 seconds before starting

  posePointRight(SPEED_STANDARD, STEP_STANDARD);  // Asymmetric front leg pose with crouched rear
  delay(random(1000, 3001));                      // Hold the point for 1 to 3 seconds
  poseStand(SPEED_STANDARD, STEP_STANDARD);       // Return to standing posture
}

#endif