#ifndef POSE_COMPOSITES_H
#define POSE_COMPOSITES_H

#include <Arduino.h>
#include "leg_primitives.h"
#include "../utils/motion_config.h"
#include "../utils/motion_speed_presets.h"  // ✅ Speed + step size presets
#include "../utils/servo_utils.h"

// 🧩 pose_composites.h
//
// This file defines Barkduino's composite poses — reusable, named configurations
// that choreograph multiple leg primitives into expressive static positions.
//
// ✅ Purpose:
// - Encapsulates common full-body poses like "Sit", "Stand", "Bow", and "Sleep"
// - Combines front and rear leg primitives with optional delays for visual clarity
// - Provides both parameterized and default overloads for flexible usage
//
// ✅ Functionality:
// - Each pose function accepts `duration` and `stepSize` to control speed and granularity
// - If no arguments are passed, defaults to SPEED_STANDARD and STEP_STANDARD
// - Poses use primitives from leg_primitives.h and mirroring-aware manual calls from servo_utils.h
// - Logging is included for serial feedback and debugging
//
// ✅ Usage Examples:
//     poseStand();                                 // Uses standard speed and granularity
//     poseBow(SPEED_SLOW, STEP_FINE);              // Slower, smoother bow
//     posePointLeft(SPEED_FAST, STEP_CHUNKY);      // Asymmetrical gesture with overrides
//     poseManual(SPEED_STANDARD, STEP_STANDARD);   // Direct servo control with symmetry

// ——— Sleep ———
void poseSleep(int duration, int stepSize) {
  Serial.println("Pose: Sleep");
  RearForward(duration, stepSize);
  delay(250);
  FrontBack(duration, stepSize);
}
void poseSleep() {
  poseSleep(SPEED_STANDARD, STEP_STANDARD);
}

// ——— Stand ———
void poseStand(int duration, int stepSize) {
  Serial.println("Pose: Stand");
  FrontStraight(duration, stepSize);
  delay(250);
  RearStraight(duration, stepSize);
}
void poseStand() {
  poseStand(SPEED_STANDARD, STEP_STANDARD);
}

// ——— Sit ———
void poseSit(int duration, int stepSize) {
  Serial.println("Pose: Sit");
  RearForward(duration, stepSize);
  delay(250);
  FrontStraight(duration, stepSize);
}
void poseSit() {
  poseSit(SPEED_STANDARD, STEP_STANDARD);
}

// ——— Bow ———
void poseBow(int duration, int stepSize) {
  Serial.println("Pose: Bow");
  RearStraight(duration, stepSize);
  delay(250);
  FrontBack(duration, stepSize);
}
void poseBow() {
  poseBow(SPEED_STANDARD, STEP_STANDARD);
}

// ——— Pounce ———
void posePounce(int duration, int stepSize) {
  Serial.println("Pose: Pounce");
  RearMidwayBack(duration, stepSize);
  delay(250);
  FrontForward(duration, stepSize);
}
void posePounce() {
  posePounce(SPEED_STANDARD, STEP_STANDARD);
}

// ——— Spread ———
void poseSpread(int duration, int stepSize) {
  Serial.println("Pose: Spread");
  FrontForward(duration, stepSize);
  delay(250);
  RearBack(duration, stepSize);
}
void poseSpread() {
  poseSpread(SPEED_STANDARD, STEP_STANDARD);
}

// ——— Manual Servo Settings ———
void poseManual(int duration, int stepSize) {
  Serial.println("Front Legs: Manually Set");
  frontLeftManual(90, duration, stepSize);
  frontRightManual(180, duration, stepSize);

  delay(250);

  Serial.println("Rear Legs: Manually Set");
  rearLeftManual(90, duration, stepSize);
  rearRightManual(180, duration, stepSize);
}
void poseManual() {
  poseManual(SPEED_STANDARD, STEP_STANDARD);
}

#endif