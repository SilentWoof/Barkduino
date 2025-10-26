#ifndef SERVO_UTILS_H
#define SERVO_UTILS_H

#include <Arduino.h>
#include <Servo.h>
#include "../utils/motion_config.h"
#include "../utils/motion_speed_presets.h"  // ✅ Speed + step size presets

// 🧩 servo_utils.h
//
// This file provides low-level servo control utilities for Barkduino,
// including manual per-leg angle setting, synchronized leg movement,
// and mirroring-aware wrappers for physical symmetry.
//
// ✅ Purpose:
// - Abstracts direct servo writes into reusable, readable functions
// - Ensures consistent mirroring logic for left-side servos
// - Supports both instant and interpolated motion via stepSize
// - Enables grouped pose setting and synchronized transitions
//
// ✅ Functionality:
// - Manual wrappers (`*_Manual`) now interpolate motion using stepSize and duration
// - `syncLegs()` interpolates motion between start and end angles for two servos
// - `syncFrontLegs()` and `syncRearLegs()` apply mirroring and angle correction
//
// ✅ Usage Examples:
//     frontLeftManual(90);                                // Instant write, no delay
//     rearRightManual(180, SPEED_SLOW);                   // Write with delay
//     setPoseManual(90, 180, 90, 180, SPEED_STANDARD);     // Set all legs at once
//     syncFrontLegs(0, 180, SPEED_SLOW, STEP_FINE);        // Smooth transition
//
// ✅ Notes:
// - Left-side servos (front/rear) are mirrored automatically
// - `syncLegs()` uses stepSize to interpolate motion for visual smoothness
// - All wrappers are designed to be callable from traits, poses, and diagnostics

// 🦴 External servo references (declared in barkduino.ino)
extern Servo front_left;
extern Servo front_right;
extern Servo rear_left;
extern Servo rear_right;

// 🖐️ Manual per-leg write wrappers (now interpolated)
inline void frontLeftManual(int angle, int duration = 0, int stepSize = SERVO_STEP_SIZE) {
  int current = 180 - front_left.read();  // unmirror
  int delta = abs(angle - current);
  int steps = max(1, delta / stepSize);
  int delayPerStep = (duration > 0) ? duration / steps : 0;
  int direction = (angle > current) ? 1 : -1;

  for (int i = 0; i <= steps; i++) {
    int intermediate = current + direction * i * stepSize;
    front_left.write(180 - intermediate);  // mirror
    if (delayPerStep > 0) delay(delayPerStep);
  }

  front_left.write(180 - angle);  // final correction
}

inline void frontRightManual(int angle, int duration = 0, int stepSize = SERVO_STEP_SIZE) {
  int current = front_right.read();
  int delta = abs(angle - current);
  int steps = max(1, delta / stepSize);
  int delayPerStep = (duration > 0) ? duration / steps : 0;
  int direction = (angle > current) ? 1 : -1;

  for (int i = 0; i <= steps; i++) {
    int intermediate = current + direction * i * stepSize;
    front_right.write(intermediate);
    if (delayPerStep > 0) delay(delayPerStep);
  }

  front_right.write(angle);
}

inline void rearLeftManual(int angle, int duration = 0, int stepSize = SERVO_STEP_SIZE) {
  int current = 180 - rear_left.read();  // unmirror
  int delta = abs(angle - current);
  int steps = max(1, delta / stepSize);
  int delayPerStep = (duration > 0) ? duration / steps : 0;
  int direction = (angle > current) ? 1 : -1;

  for (int i = 0; i <= steps; i++) {
    int intermediate = current + direction * i * stepSize;
    rear_left.write(180 - intermediate);  // mirror
    if (delayPerStep > 0) delay(delayPerStep);
  }

  rear_left.write(180 - angle);
}

inline void rearRightManual(int angle, int duration = 0, int stepSize = SERVO_STEP_SIZE) {
  int current = rear_right.read();
  int delta = abs(angle - current);
  int steps = max(1, delta / stepSize);
  int delayPerStep = (duration > 0) ? duration / steps : 0;
  int direction = (angle > current) ? 1 : -1;

  for (int i = 0; i <= steps; i++) {
    int intermediate = current + direction * i * stepSize;
    rear_right.write(intermediate);
    if (delayPerStep > 0) delay(delayPerStep);
  }

  rear_right.write(angle);
}

// 🧩 Optional grouped pose setter
inline void setPoseManual(int fl, int fr, int rl, int rr, int duration = 0, int stepSize = SERVO_STEP_SIZE) {
  frontLeftManual(fl, duration, stepSize);
  frontRightManual(fr, duration, stepSize);
  rearLeftManual(rl, duration, stepSize);
  rearRightManual(rr, duration, stepSize);
}

// 🔁 Sweep two legs in sync from independent start/end angles
void syncLegs(Servo& left, Servo& right,
              int startLeft, int endLeft,
              int startRight, int endRight,
              int delayMs,
              bool mirrorLeft = false, bool mirrorRight = false,
              int stepSize = SERVO_STEP_SIZE) {
  int stepsLeft  = abs(endLeft - startLeft) / stepSize;
  int stepsRight = abs(endRight - startRight) / stepSize;
  int steps = max(stepsLeft, stepsRight);

  for (int i = 0; i <= steps; i++) {
    int leftAngle  = startLeft  + ((endLeft  > startLeft)  ? 1 : -1) * min(i, stepsLeft)  * stepSize;
    int rightAngle = startRight + ((endRight > startRight) ? 1 : -1) * min(i, stepsRight) * stepSize;

    if (mirrorLeft)  left.write(180 - leftAngle);  else left.write(leftAngle);
    if (mirrorRight) right.write(180 - rightAngle); else right.write(rightAngle);

    delay(delayMs);
  }

  left.write(mirrorLeft ? 180 - endLeft : endLeft);
  right.write(mirrorRight ? 180 - endRight : endRight);
}

// 🦵 Front leg sync wrapper (left leg is mirrored)
void syncFrontLegs(int leftTarget, int rightTarget, int duration, int stepSize = SERVO_STEP_SIZE) {
  int leftStartUnmirrored = 180 - front_left.read();  // ✅ undo mirroring
  int rightStart = front_right.read();

  syncLegs(front_left, front_right,
           leftStartUnmirrored, leftTarget,
           rightStart, rightTarget,
           duration, true, false, stepSize);
}

// 🦵 Rear leg sync wrapper (rear left mirrored)
void syncRearLegs(int leftTarget, int rightTarget, int duration, int stepSize = SERVO_STEP_SIZE) {
  int leftStartUnmirrored = 180 - rear_left.read();  // ✅ undo mirroring
  int rightStart = rear_right.read();

  syncLegs(rear_left, rear_right,
           leftStartUnmirrored, leftTarget,
           rightStart, rightTarget,
           duration, true, false, stepSize);
}

#endif