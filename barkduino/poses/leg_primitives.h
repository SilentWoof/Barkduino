#ifndef LEG_PRIMITIVES_H
#define LEG_PRIMITIVES_H

#include <Arduino.h>
#include <Servo.h>
#include "../utils/motion_config.h"         // ⏱️ Centralized motion timing
#include "../utils/motion_speed_presets.h"  // 🎚️ Speed + step size presets
#include "../utils/servo_utils.h"           // ✅ Updated sync wrappers

// 🧩 Primitive Leg Positions
//
// This file defines reusable, named leg positions for Barkduino's front and rear servos.
// Each primitive represents a specific pose (e.g. folded forward, straight, folded back).
//
// ✅ Usage:
// - These functions are called by traits and modes to choreograph motion.
// - Each primitive accepts optional `duration` and `stepSize` arguments:
//     - `duration` controls speed (default: DEFAULT_SYNC_DURATION)
//     - `stepSize` controls granularity (default: SERVO_STEP_SIZE)
// - If no arguments are passed, both defaults are used.
//
// ✅ Examples:
//     FrontBack();                                // Uses default speed and granularity
//     RearStraight(SPEED_SLOW);                   // Overrides speed only
//     FrontForward(SPEED_FAST, STEP_CHUNKY);      // Overrides both

// ——— Front ———
inline void FrontForward(int duration = DEFAULT_SYNC_DURATION, int stepSize = SERVO_STEP_SIZE) {
  Serial.println("Front legs: folded forward");
  syncFrontLegs(180, 180, duration, stepSize);
}

inline void FrontMidwayForward(int duration = DEFAULT_SYNC_DURATION, int stepSize = SERVO_STEP_SIZE) {
  Serial.println("Front legs: midway to folded forward");
  syncFrontLegs(135, 135, duration, stepSize);
}

inline void FrontStraight(int duration = DEFAULT_SYNC_DURATION, int stepSize = SERVO_STEP_SIZE) {
  Serial.println("Front legs: straight");
  syncFrontLegs(90, 90, duration, stepSize);
}

inline void FrontMidwayBack(int duration = DEFAULT_SYNC_DURATION, int stepSize = SERVO_STEP_SIZE) {
  Serial.println("Front legs: midway to folded back");
  syncFrontLegs(45, 45, duration, stepSize);
}

inline void FrontBack(int duration = DEFAULT_SYNC_DURATION, int stepSize = SERVO_STEP_SIZE) {
  Serial.println("Front legs: folded back");
  syncFrontLegs(0, 0, duration, stepSize);
}

// ——— Rear ———
inline void RearForward(int duration = DEFAULT_SYNC_DURATION, int stepSize = SERVO_STEP_SIZE) {
  Serial.println("Rear legs: folded forward");
  syncRearLegs(180, 180, duration, stepSize);
}

inline void RearMidwayForward(int duration = DEFAULT_SYNC_DURATION, int stepSize = SERVO_STEP_SIZE) {
  Serial.println("Rear legs: midway to folded forward");
  syncRearLegs(115, 115, duration, stepSize);
}

inline void RearStraight(int duration = DEFAULT_SYNC_DURATION, int stepSize = SERVO_STEP_SIZE) {
  Serial.println("Rear legs: straight");
  syncRearLegs(70, 70, duration, stepSize);
}

inline void RearMidwayBack(int duration = DEFAULT_SYNC_DURATION, int stepSize = SERVO_STEP_SIZE) {
  Serial.println("Rear legs: midway to folded back");
  syncRearLegs(25, 25, duration, stepSize);
}

inline void RearBack(int duration = DEFAULT_SYNC_DURATION, int stepSize = SERVO_STEP_SIZE) {
  Serial.println("Rear legs: folded back");
  syncRearLegs(0, 0, duration, stepSize);
}

#endif