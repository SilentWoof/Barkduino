#ifndef TRAIT_BOW_H
#define TRAIT_BOW_H

#include <Arduino.h>
#include "../poses/leg_primitives.h"
#include "../utils/motion_speed_presets.h"  // ✅ Speed + step size presets

// 🐾 trait_bow.h
//
// This trait performs a slow, expressive bow gesture using direct leg primitives.
//
// ✅ Purpose:
// - Demonstrates a graceful front-leg fold with rear-leg support
// - Uses intentionally mixed speed settings for dramatic effect
// - Returns to a neutral front-leg posture after holding
//
// ✅ Functionality:
// - Rear legs straighten at SPEED_STANDARD
// - Front legs fold and return using SPEED_DEAD_SLOW and STEP_FINE for smooth motion
// - Includes timed delays for pacing and emphasis
//
// ✅ Usage:
//     trait_bow();  // Executes the full bow gesture sequence

void trait_bow() {
  Serial.println("Trait: Bow");

  delay(1000);  // Brief pause before starting

  RearStraight(SPEED_STANDARD, STEP_STANDARD);         // Rear legs straighten for support
  FrontBack(SPEED_DEAD_SLOW, STEP_FINE);               // Front legs fold forward slowly
  delay(2000);                                          // Hold the bow
  FrontStraight(SPEED_DEAD_SLOW, STEP_FINE);           // Return to neutral slowly
  delay(500);                                           // Final pause
}

#endif