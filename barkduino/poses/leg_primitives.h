#ifndef LEG_PRIMITIVES_H
#define LEG_PRIMITIVES_H

#include <Arduino.h>
#include <Servo.h>

// External servo references (declared in main sketch)
extern Servo front_left;
extern Servo front_right;
extern Servo rear_left;
extern Servo rear_right;

// Synchronization helpers (declared in main sketch)
void syncRearLegs(int leftTarget, int rightTarget, int duration = 500);
void syncFrontLegs(int leftTarget, int rightTarget, int duration = 500);

// 🧩 Primitive Leg Positions

void rearLegsFoldedForward() {
  Serial.println("Rear legs: folded forward");
  syncRearLegs(0, 180);
}

void rearLegsStraight() {
  Serial.println("Rear legs: straight");
  syncRearLegs(100, 60);
}

void frontLegsFoldedBack() {
  Serial.println("Front legs: folded back");
  syncFrontLegs(160, 20);
}

void frontLegsStraight() {
  Serial.println("Front legs: straight");
  syncFrontLegs(60, 110);
}

#endif