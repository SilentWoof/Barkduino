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

// Front
void FrontForward() {
  Serial.println("Front legs: folded forward");
  syncFrontLegs(0, 180);
}

void FrontMidwayForward() {
  Serial.println("Front legs: midway to folded forward");
  syncFrontLegs(30, 145);
}

void FrontStraight() {
  Serial.println("Front legs: straight");
  syncFrontLegs(60, 110);
}

void FrontMidwayBack() {
  Serial.println("Front legs: midway to folded back");
  syncFrontLegs(110, 65);
}

void FrontBack() {
  Serial.println("Front legs: folded back");
  syncFrontLegs(160, 20);
}

// Rear
void RearForward() {
  Serial.println("Rear legs: folded forward");
  syncRearLegs(0, 180);
}

void RearMidwayForward() {
  Serial.println("Rear legs: midway to folded forward");
  syncRearLegs(50, 120);
}

void RearStraight() {
  Serial.println("Rear legs: straight");
  syncRearLegs(100, 60);
}

void RearMidwayBack() {
  Serial.println("Rear legs: midway to folded back");
  syncRearLegs(140, 20);
}

void RearBack() {
  Serial.println("Rear legs: folded back");
  syncRearLegs(180, 0);
}

#endif
