#ifndef TRAIT_JUMP_H
#define TRAIT_JUMP_H

#include <Arduino.h>
#include "../poses/pose_composites.h"
#include "../utils/motion_speed_presets.h"  // ✅ Speed + step size presets

// 🐾 trait_jump.h
//
// This trait performs a stylized "jump" gesture using Barkduino's composite pose system.
//
// ✅ Purpose:
// - Simulates energetic jumping through coordinated leg movement
// - Adds personality and rhythm to Barkduino's motion vocabulary
//
// ✅ Functionality:
// - Repeats a jump loop 5–10 times
// - Each jump starts with a crouch and ends with a mid-air extension
// - Uses SPEED_FAST and STEP_CHUNKY for expressive motion
// - Returns to a neutral standing posture
//
// ✅ Usage:
//     trait_jump();  // Executes the full jump sequence

void trait_jump() {
  Serial.println("Trait: Jump");

  delay(500);  // Prep pause

  const int jumpCount = random(5, 11);  // 5 to 10 jumps

  for (int i = 0; i < jumpCount; i++) {
    Serial.print("Jump "); Serial.println(i + 1);

    // 🐾 Crouch phase
    FrontMidwayBack(SPEED_FAST, STEP_CHUNKY);
    RearMidwayForward(SPEED_FAST, STEP_CHUNKY);
    delay(150);  // Simulate compression

    // 🐾 Extension phase
    FrontMidwayForward(SPEED_FAST, STEP_CHUNKY);
    RearMidwayBack(SPEED_FAST, STEP_CHUNKY);
    delay(200);  // Simulate airtime
  }

  poseStand(SPEED_STANDARD, STEP_STANDARD);  // Return to neutral
}

#endif