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

  RearMidwayBack(SPEED_STANDARD, STEP_STANDARD);
  delay(250);

  Serial.println("Front legs: asymmetrical point");

  // 🧪 Debug: check current front_left angle before sweep
  int frontLeftCurrent = 180 - front_left.read();  // unmirror
  int frontLeftTarget = 180;
  int frontLeftDelta = abs(frontLeftTarget - frontLeftCurrent);
  int frontLeftSteps = max(1, frontLeftDelta / STEP_FINE);
  int frontLeftDelayPerStep = max(1, SPEED_DEAD_SLOW / frontLeftSteps);

  Serial.print("front_left.read() before sweep = ");
  Serial.println(front_left.read());
  Serial.print("frontLeft sweep steps = ");
  Serial.println(frontLeftSteps);
  Serial.print("frontLeft delay per step = ");
  Serial.println(frontLeftDelayPerStep);

  // 🐢 Slow sweep first for visual clarity
  frontLeftManual(180, 1, STEP_CHUNKY);
  frontRightManual(90, SPEED_STANDARD, STEP_STANDARD);
  delay(random(2000, 4001));                            // Hold the point for 2 to 4 seconds
  frontLeftManual(90, 1000, STEP_FINE);
  poseStand(SPEED_STANDARD, STEP_STANDARD);             // Return to standing posture
}

#endif
