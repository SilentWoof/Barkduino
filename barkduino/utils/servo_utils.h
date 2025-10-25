#ifndef SERVO_UTILS_H
#define SERVO_UTILS_H

#include <Arduino.h>
#include <Servo.h>
#include "../configs/motion_config.h"

// 🔧 Sweep two servos in sync over a duration
void sweepPair(Servo& s1, int start1, int end1,
               Servo& s2, int start2, int end2,
               int duration_ms) {
  const int steps = 20;
  for (int i = 0; i <= steps; i++) {
    float t = (float)i / steps;
    s1.write(start1 + (end1 - start1) * t);
    s2.write(start2 + (end2 - start2) * t);
    delay(duration_ms / steps);
  }
}

// 🔧 Sync rear legs
void syncRearLegs(int leftTarget, int rightTarget, int duration = DEFAULT_SYNC_DURATION) {
  extern Servo rear_left;
  extern Servo rear_right;
  sweepPair(rear_left, rear_left.read(), leftTarget,
            rear_right, rear_right.read(), rightTarget, duration);
}

// 🔧 Sync front legs
void syncFrontLegs(int leftTarget, int rightTarget, int duration = DEFAULT_SYNC_DURATION) {
  extern Servo front_left;
  extern Servo front_right;
  sweepPair(front_left, front_left.read(), leftTarget,
            front_right, front_right.read(), rightTarget, duration);
}

#endif