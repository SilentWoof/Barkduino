#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include <Arduino.h>
#include <Servo.h>
#include "../poses/pose_composites.h"

// 🦿 Waggle a leg for 3 seconds
void waggleLeg(Servo& leg, const char* label) {
  Serial.print("Waggling "); Serial.println(label);
  int center = leg.read();
  for (unsigned long t = millis(); millis() - t < 3000;) {
    leg.write(center - 20); delay(300);
    leg.write(center + 20); delay(300);
  }
  leg.write(center); delay(500);
}

// 🛠️ Mode 4: Waggle test dispatcher
void runWaggleTest() {
  extern Servo front_left;
  extern Servo front_right;
  extern Servo rear_left;
  extern Servo rear_right;

  Serial.println("Mode 4 — Waggle Test");
  poseStand();

  waggleLeg(front_left, "Front Left");
  waggleLeg(front_right, "Front Right");
  waggleLeg(rear_left, "Rear Left");
  waggleLeg(rear_right, "Rear Right");

  Serial.println("Waggle test complete.");
  while (true);
}

#endif