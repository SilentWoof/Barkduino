#ifndef POSE_COMPOSITES_H
#define POSE_COMPOSITES_H

#include <Arduino.h>
#include "leg_primitives.h"
#include "../utils/motion_config.h"
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
// - Each pose function accepts an optional `duration` argument to control motion speed
// - If no duration is passed, the system defaults to `DEFAULT_SYNC_DURATION`
// - Poses use primitives from `leg_primitives.h` and mirroring-aware manual calls from `servo_utils.h`
// - Logging is included for serial feedback and debugging
//
// ✅ Usage Examples:
//     poseStand();                          // Uses default speed
//     poseBow(SPEED_SLOW);                  // Slower, expressive bow
//     posePointLeft(SPEED_FAST);            // Asymmetrical gesture with speed override
//     poseManual(SPEED_STANDARD);           // Direct servo control with symmetry
//
// ✅ Notes:
// - Composite poses are static — they define a final configuration, not dynamic motion
// - Traits and modes may call these poses as part of larger behavior sequences
// - Manual poses allow direct angle control for calibration or expressive gestures

// ——— Sleep (static only) ———
void poseSleep(int duration) {
  Serial.println("Pose: Sleep");
  RearForward(duration);
  delay(250);
  FrontBack(duration);
}
void poseSleep() {
  poseSleep(DEFAULT_SYNC_DURATION);
}

// ——— Stand ———
void poseStand(int duration) {
  Serial.println("Pose: Stand");
  FrontStraight(duration);
  delay(250);
  RearStraight(duration);
}
void poseStand() {
  poseStand(DEFAULT_SYNC_DURATION);
}

// ——— Sit ———
void poseSit(int duration) {
  Serial.println("Pose: Sit");
  RearForward(duration);
  delay(250);
  FrontStraight(duration);
}
void poseSit() {
  poseSit(DEFAULT_SYNC_DURATION);
}

// ——— Bow ———
void poseBow(int duration) {
  Serial.println("Pose: Bow");
  RearStraight(duration);
  delay(250);
  FrontBack(duration);
}
void poseBow() {
  poseBow(DEFAULT_SYNC_DURATION);
}

// ——— Pounce ———
void posePounce(int duration) {
  Serial.println("Pose: Pounce");
  RearMidwayBack(duration);
  delay(250);
  FrontForward(duration);
}
void posePounce() {
  posePounce(DEFAULT_SYNC_DURATION);
}

// ——— Spread ———
void poseSpread(int duration) {
  Serial.println("Pose: Spread");
  FrontForward(duration);
  delay(250);
  RearBack(duration);
}
void poseSpread() {
  poseSpread(DEFAULT_SYNC_DURATION);
}

// ——— Point Left ———
void posePointLeft(int duration) {
  Serial.println("Pose: Point Left");
  RearMidwayBack(duration);
  delay(250);
  Serial.println("Front legs: asymmetrical point");
  frontLeftManual(180, duration);  // ✅ Forward (mirrored)
  frontRightManual(90, duration);  // ✅ Straight
}
void posePointLeft() {
  posePointLeft(DEFAULT_SYNC_DURATION);
}

// ——— Point Right ———
void posePointRight(int duration) {
  Serial.println("Pose: Point Right");
  RearMidwayBack(duration);
  delay(250);
  Serial.println("Front legs: asymmetrical point");
  frontLeftManual(90, duration);   // ✅ Straight (mirrored)
  frontRightManual(180, duration); // ✅ Forward
}
void posePointRight() {
  posePointRight(DEFAULT_SYNC_DURATION);
}

// ——— Manual Servo Settings ———
// Sets each leg independently using mirroring-aware wrappers.
// Ensures physical symmetry regardless of mounting orientation.
// Includes logging and optional delay for visual confirmation.

void poseManual(int duration) {
  Serial.println("Front Legs: Manually Set");
  frontLeftManual(90, duration);     // 🦵 Front Left — mirrored automatically
  frontRightManual(180, duration);   // 🦵 Front Right — direct angle

  delay(250);  // Optional pause between front and rear transitions

  Serial.println("Rear Legs: Manually Set");
  rearLeftManual(90, duration);      // 🦵 Rear Left — mirrored automatically
  rearRightManual(180, duration);    // 🦵 Rear Right — direct angle
}
void poseManual() {
  poseManual(DEFAULT_SYNC_DURATION);
}

#endif