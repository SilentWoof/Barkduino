#ifndef TRAIT_WAGGLE_LEFT_H
#define TRAIT_WAGGLE_LEFT_H

#include <Arduino.h>
#include "../poses/pose_composites.h"
#include "../utils/motion_speed_presets.h"  // ✅ Speed + step size presets

// 🐾 trait_waggle_left.h
//
// This trait performs a playful "waggle left" gesture using Barkduino's composite pose system.
//
// ✅ Purpose:
// - Simulates a waving motion with the left front leg
// - Uses a crouched rear stance for balance and expressiveness
// - Returns to a neutral standing posture after waggle sequence
//
// ✅ Functionality:
// - Rear legs crouch using `RearMidwayBack()`
// - Left front leg alternates between two angles five times
// - Uses SPEED_SLOW and STEP_FINE for expressive motion
// - Returns to `poseStand()` for reset
//
// ✅ Usage:
//     trait_waggle_left();  // Executes the full waggle-left gesture sequence

void trait_waggle_left() {
  Serial.println("Trait: Waggle Left");

  delay(500);  // Wait before starting

  RearMidwayBack(SPEED_STANDARD, STEP_STANDARD);
  delay(250);

  Serial.println("Front left leg: waggle sequence");

  const int waggleUp = 180;
  const int waggleDown = 140;
  const int waggleCount = random(5, 16);  // Randomize number of waggles between 10 and 20

  for (int i = 0; i < waggleCount; i++) {
    Serial.print("Waggle "); Serial.println(i + 1);
    frontLeftManual(waggleUp, SPEED_SLOW, STEP_FINE);
    delay(100);
    frontLeftManual(waggleDown, SPEED_SLOW, STEP_FINE);
    delay(100);
  }

  frontLeftManual(90, SPEED_STANDARD, STEP_STANDARD);  // Reset leg
  poseStand(SPEED_STANDARD, STEP_STANDARD);            // Return to standing posture
}

#endif