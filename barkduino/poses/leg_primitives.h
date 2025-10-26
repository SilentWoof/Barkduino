#ifndef LEG_PRIMITIVES_H
#define LEG_PRIMITIVES_H

#include <Arduino.h>
#include <Servo.h>
#include "../utils/motion_config.h"         // ⏱️ Centralized motion timing
#include "../utils/motion_speed_presets.h"  // 🎚️ Speed + step size presets
#include "../utils/servo_utils.h"           // ✅ Updated sync wrappers

// 🧩 Primitive Leg Positions (with optional stepSize)

// ——— Front (custom speed + optional step size) ———
inline void FrontForward(int duration, int stepSize = SERVO_STEP_SIZE) {
  Serial.println("Front legs: folded forward");
  syncFrontLegs(180, 180, duration, stepSize);
}

inline void FrontMidwayForward(int duration, int stepSize = SERVO_STEP_SIZE) {
  Serial.println("Front legs: midway to folded forward");
  syncFrontLegs(135, 135, duration, stepSize);
}

inline void FrontStraight(int duration, int stepSize = SERVO_STEP_SIZE) {
  Serial.println("Front legs: straight");
  syncFrontLegs(90, 90, duration, stepSize);
}

inline void FrontMidwayBack(int duration, int stepSize = SERVO_STEP_SIZE) {
  Serial.println("Front legs: midway to folded back");
  syncFrontLegs(45, 45, duration, stepSize);
}

inline void FrontBack(int duration, int stepSize = SERVO_STEP_SIZE) {
  Serial.println("Front legs: folded back");
  syncFrontLegs(0, 0, duration, stepSize);
}

// ——— Rear (custom speed + optional step size) ———
inline void RearForward(int duration, int stepSize = SERVO_STEP_SIZE) {
  Serial.println("Rear legs: folded forward");
  syncRearLegs(180, 180, duration, stepSize);
}

inline void RearMidwayForward(int duration, int stepSize = SERVO_STEP_SIZE) {
  Serial.println("Rear legs: midway to folded forward");
  syncRearLegs(115, 115, duration, stepSize);
}

inline void RearStraight(int duration, int stepSize = SERVO_STEP_SIZE) {
  Serial.println("Rear legs: straight");
  syncRearLegs(70, 70, duration, stepSize);
}

inline void RearMidwayBack(int duration, int stepSize = SERVO_STEP_SIZE) {
  Serial.println("Rear legs: midway to folded back");
  syncRearLegs(25, 25, duration, stepSize);
}

inline void RearBack(int duration, int stepSize = SERVO_STEP_SIZE) {
  Serial.println("Rear legs: folded back");
  syncRearLegs(0, 0, duration, stepSize);
}

// ——— Front (default speed) ———
inline void FrontForward()         { FrontForward(DEFAULT_SYNC_DURATION); }
inline void FrontMidwayForward()   { FrontMidwayForward(DEFAULT_SYNC_DURATION); }
inline void FrontStraight()        { FrontStraight(DEFAULT_SYNC_DURATION); }
inline void FrontMidwayBack()      { FrontMidwayBack(DEFAULT_SYNC_DURATION); }
inline void FrontBack()            { FrontBack(DEFAULT_SYNC_DURATION); }

// ——— Rear (default speed) ———
inline void RearForward()          { RearForward(DEFAULT_SYNC_DURATION); }
inline void RearMidwayForward()    { RearMidwayForward(DEFAULT_SYNC_DURATION); }
inline void RearStraight()         { RearStraight(DEFAULT_SYNC_DURATION); }
inline void RearMidwayBack()       { RearMidwayBack(DEFAULT_SYNC_DURATION); }
inline void RearBack()             { RearBack(DEFAULT_SYNC_DURATION); }

#endif