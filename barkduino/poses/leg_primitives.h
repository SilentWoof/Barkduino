#ifndef LEG_PRIMITIVES_H
#define LEG_PRIMITIVES_H

#include <Arduino.h>
#include <Servo.h>
#include "../configs/motion_config.h"  // ⏱️ Centralized motion timing

// External servo references (declared in main sketch)
extern Servo front_left;
extern Servo front_right;
extern Servo rear_left;
extern Servo rear_right;

// Synchronization helpers (declared in main sketch)
void syncRearLegs(int leftTarget, int rightTarget, int duration);
void syncFrontLegs(int leftTarget, int rightTarget, int duration);

// 🧩 Primitive Leg Positions

// ——— Front (default speed) ———
void FrontForward()         { FrontForward(DEFAULT_SYNC_DURATION); }
void FrontMidwayForward()   { FrontMidwayForward(DEFAULT_SYNC_DURATION); }
void FrontStraight()        { FrontStraight(DEFAULT_SYNC_DURATION); }
void FrontMidwayBack()      { FrontMidwayBack(DEFAULT_SYNC_DURATION); }
void FrontBack()            { FrontBack(DEFAULT_SYNC_DURATION); }

// ——— Rear (default speed) ———
void RearForward()          { RearForward(DEFAULT_SYNC_DURATION); }
void RearMidwayForward()    { RearMidwayForward(DEFAULT_SYNC_DURATION); }
void RearStraight()         { RearStraight(DEFAULT_SYNC_DURATION); }
void RearMidwayBack()       { RearMidwayBack(DEFAULT_SYNC_DURATION); }
void RearBack()             { RearBack(DEFAULT_SYNC_DURATION); }

// ——— Front (custom speed) ———
void FrontForward(int duration) {
  Serial.println("Front legs: folded forward");
  syncFrontLegs(0, 180, duration);
}

void FrontMidwayForward(int duration) {
  Serial.println("Front legs: midway to folded forward");
  syncFrontLegs(30, 145, duration);
}

void FrontStraight(int duration) {
  Serial.println("Front legs: straight");
  syncFrontLegs(60, 110, duration);
}

void FrontMidwayBack(int duration) {
  Serial.println("Front legs: midway to folded back");
  syncFrontLegs(110, 65, duration);
}

void FrontBack(int duration) {
  Serial.println("Front legs: folded back");
  syncFrontLegs(160, 20, duration);
}

// ——— Rear (custom speed) ———
void RearForward(int duration) {
  Serial.println("Rear legs: folded forward");
  syncRearLegs(0, 180, duration);
}

void RearMidwayForward(int duration) {
  Serial.println("Rear legs: midway to folded forward");
  syncRearLegs(50, 120, duration);
}

void RearStraight(int duration) {
  Serial.println("Rear legs: straight");
  syncRearLegs(100, 60, duration);
}

void RearMidwayBack(int duration) {
  Serial.println("Rear legs: midway to folded back");
  syncRearLegs(150, 20, duration);
}

void RearBack(int duration) {
  Serial.println("Rear legs: folded back");
  syncRearLegs(180, 0, duration);
}

#endif