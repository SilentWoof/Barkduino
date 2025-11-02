#ifndef TRAIT_WAGGLE_RIGHT_H
#define TRAIT_WAGGLE_RIGHT_H

#include <Arduino.h>
#include "../poses/pose_composites.h"
#include "../utils/motion_speed_presets.h"  // ✅ Speed + step size presets

// 🐾 trait_waggle_right.h
//
// This trait performs a playful "waggle right" gesture using Barkduino's composite pose system.
//
// ✅ Purpose:
// - Simulates a waving motion with the right front leg
// - Uses a crouched rear stance for balance and expressiveness
// - Returns to a neutral standing posture after waggle sequence
//
// ✅ Functionality:
// - Rear legs crouch using `RearMidwayBack()`
// - Right front leg alternates between two angles multiple times
// - Uses SPEED_SLOW and STEP_FINE for expressive motion
// - Returns to `poseStand()` for reset
//
// ✅ Usage:
//     trait_waggle_right();  // Executes the full waggle-right gesture sequence

void trait_waggle_right() {
  Serial.println("Trait: Waggle Right");

  delay(500);  // Wait before starting

  RearMidwayBack(SPEED_STANDARD, STEP_STANDARD);
  delay(250);

  Serial.println("Front right leg: waggle sequence");

  const int waggleUp = 180;
  const int waggleDown = 140;
  const int waggleCount = random(5, 16);  // Randomize number of waggles between 10 and 20

  for (int i = 0; i < waggleCount; i++) {
    Serial.print("Waggle "); Serial.println(i + 1);
    frontRightManual(waggleUp, SPEED_SLOW, STEP_FINE);
    delay(100);
    frontRightManual(waggleDown, SPEED_SLOW, STEP_FINE);
    delay(100);
  }

  frontRightManual(90, SPEED_STANDARD, STEP_STANDARD);  // Reset leg
  poseStand(SPEED_STANDARD, STEP_STANDARD);             // Return to standing posture
}

#endif