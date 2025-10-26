#ifndef TRAIT_POUNCE_H
#define TRAIT_POUNCE_H

#include <Arduino.h>
#include "../poses/pose_composites.h"
#include "../poses/leg_primitives.h"
#include "../utils/motion_speed_presets.h"  // ✅ Speed + step size presets

// 🐾 trait_pounce.h
//
// This trait performs a playful "pounce" gesture using a mix of composite poses and direct leg primitives.
//
// ✅ Purpose:
// - Simulates a crouch-pounce motion with alternating front leg extensions
// - Uses expressive timing and randomized delays for natural behavior
// - Returns to a neutral standing posture at the end
//
// ✅ Functionality:
// - Calls `posePounce()` and `FrontStraight()` with SPEED_STANDARD and STEP_STANDARD
// - Alternates between crouch and extension with randomized hold durations
// - Ends with `poseStand()` to reset posture
//
// ✅ Usage:
//     trait_pounce();  // Executes the full pounce gesture sequence

void trait_pounce() {
  Serial.println("Trait: Pounce");

  posePounce(SPEED_STANDARD, STEP_STANDARD);         // Crouch with rear legs midway back, front legs forward
  delay(750);                                         // Initial hold
  FrontStraight(SPEED_STANDARD, STEP_STANDARD);       // Extend front legs
  delay(random(100, 1001));                           // Brief hold
  posePounce(SPEED_STANDARD, STEP_STANDARD);          // Return to pounce
  delay(random(100, 3001));                           // Variable hold
  FrontStraight(SPEED_STANDARD, STEP_STANDARD);       // Extend again
  delay(random(100, 1001));                           // Brief hold
  posePounce(SPEED_STANDARD, STEP_STANDARD);          // Return again
  delay(random(100, 3001));                           // Final hold
  poseStand(SPEED_STANDARD, STEP_STANDARD);           // Final stand
}

#endif