#ifndef SERVO_UTILS_H
#define SERVO_UTILS_H

#include <Arduino.h>
#include <Servo.h>

// 🦴 External servo references
extern Servo front_left;
extern Servo front_right;
extern Servo rear_left;
extern Servo rear_right;

// 🔁 Sweep two servos in sync with speed control
void sweepPair(Servo& s1, Servo& s2, int start1, int end1, int start2, int end2, int delayMs) {
  int steps = abs(end1 - start1);
  for (int i = 0; i <= steps; i++) {
    int angle1 = start1 + ((end1 - start1) > 0 ? i : -i);
    int angle2 = start2 + ((end2 - start2) > 0 ? i : -i);
    s1.write(angle1);
    s2.write(angle2);
    delay(delayMs);
  }
}

// 🔁 Sweep a leg pair with speed control
void syncLegs(Servo& left, Servo& right, int startAngle, int endAngle, int delayMs) {
  int steps = abs(endAngle - startAngle);
  for (int i = 0; i <= steps; i++) {
    int angle = startAngle + ((endAngle - startAngle) > 0 ? i : -i);
    left.write(angle);
    right.write(angle);
    delay(delayMs);
  }
}

#endif