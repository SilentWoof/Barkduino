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

  RearMidwayBack(SPEED_STANDARD, STEP_STANDARD);
  delay(250);

  Serial.println("Front legs: asymmetrical point");

  // 🧪 Debug: check current front_right angle before sweep
  int frontRightCurrent = 180 - front_right.read();  // unmirror
  int frontRightTarget = 180;
  int frontRightDelta = abs(frontRightTarget - frontRightCurrent);
  int frontRightSteps = max(1, frontRightDelta / STEP_FINE);
  int frontRightDelayPerStep = max(1, SPEED_DEAD_SLOW / frontRightSteps);

  Serial.print("front_right.read() before sweep = ");
  Serial.println(front_right.read());
  Serial.print("frontRight sweep steps = ");
  Serial.println(frontRightSteps);
  Serial.print("frontRight delay per step = ");
  Serial.println(frontRightDelayPerStep);

  // 🐢 Slow sweep first for visual clarity
  frontRightManual(180, 1, STEP_CHUNKY);
  frontLeftManual(90, SPEED_STANDARD, STEP_STANDARD);
  delay(random(2000, 4001));                            // Hold the point for 2 to 4 seconds
  frontRightManual(90, 1000, STEP_FINE);
  poseStand(SPEED_STANDARD, STEP_STANDARD);             // Return to standing posture
}

#endif