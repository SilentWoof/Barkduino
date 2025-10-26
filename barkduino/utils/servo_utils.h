#ifndef SERVO_UTILS_H
#define SERVO_UTILS_H

#include <Arduino.h>
#include <Servo.h>
#include "../utils/motion_config.h"

// 🦴 External servo references (declared in barkduino.ino)
extern Servo front_left;
extern Servo front_right;
extern Servo rear_left;
extern Servo rear_right;

// 🖐️ Manual per-leg write wrappers
inline void frontLeftManual(int angle, int duration = 0) {
  int mirrored = 180 - angle;
  Serial.print("front_left → "); Serial.println(mirrored);
  front_left.write(mirrored);
  if (duration > 0) delay(duration);
}

inline void frontRightManual(int angle, int duration = 0) {
  Serial.print("front_right → "); Serial.println(angle);
  front_right.write(angle);
  if (duration > 0) delay(duration);
}

inline void rearLeftManual(int angle, int duration = 0) {
  int mirrored = 180 - angle;
  Serial.print("rear_left → "); Serial.println(mirrored);
  rear_left.write(mirrored);
  if (duration > 0) delay(duration);
}

inline void rearRightManual(int angle, int duration = 0) {
  Serial.print("rear_right → "); Serial.println(angle);
  rear_right.write(angle);
  if (duration > 0) delay(duration);
}

// 🧩 Optional grouped pose setter
inline void setPoseManual(int fl, int fr, int rl, int rr, int duration = 0) {
  frontLeftManual(fl, duration);
  frontRightManual(fr, duration);
  rearLeftManual(rl, duration);
  rearRightManual(rr, duration);
}

// 🔁 Sweep two legs in sync from independent start/end angles
void syncLegs(Servo& left, Servo& right,
              int startLeft, int endLeft,
              int startRight, int endRight,
              int delayMs,
              bool mirrorLeft = false, bool mirrorRight = false) {
  int stepsLeft  = abs(endLeft - startLeft) / SERVO_STEP_SIZE;
  int stepsRight = abs(endRight - startRight) / SERVO_STEP_SIZE;
  int steps = max(stepsLeft, stepsRight);

  for (int i = 0; i <= steps; i++) {
    int leftAngle  = startLeft  + ((endLeft  > startLeft)  ? 1 : -1) * min(i, stepsLeft)  * SERVO_STEP_SIZE;
    int rightAngle = startRight + ((endRight > startRight) ? 1 : -1) * min(i, stepsRight) * SERVO_STEP_SIZE;

    if (mirrorLeft)  left.write(180 - leftAngle);  else left.write(leftAngle);
    if (mirrorRight) right.write(180 - rightAngle); else right.write(rightAngle);

    delay(delayMs);
  }

  left.write(mirrorLeft ? 180 - endLeft : endLeft);
  right.write(mirrorRight ? 180 - endRight : endRight);
}

// 🦵 Front leg sync wrapper (left leg is mirrored)
void syncFrontLegs(int leftTarget, int rightTarget, int duration) {
  int leftStartUnmirrored = 180 - front_left.read();  // ✅ undo mirroring
  int rightStart = front_right.read();

  syncLegs(front_left, front_right,
           leftStartUnmirrored, leftTarget,
           rightStart, rightTarget,
           duration, true, false);
}

// 🦵 Rear leg sync wrapper (rear left mirrored)
void syncRearLegs(int leftTarget, int rightTarget, int duration) {
  int leftStartUnmirrored = 180 - rear_left.read();  // ✅ undo mirroring
  int rightStart = rear_right.read();

  syncLegs(rear_left, rear_right,
           leftStartUnmirrored, leftTarget,
           rightStart, rightTarget,
           duration, true, false);
}

#endif