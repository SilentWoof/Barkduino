#ifndef TRAIT_WAIT_H
#define TRAIT_WAIT_H

#include <Arduino.h>
#include "../utils/motion_speed_presets.h"  // ✅ Included for consistency

// 🐾 trait_wait.h
//
// This trait performs a passive wait or pause in the motion sequence.
//
// ✅ Purpose:
// - Introduces a timed delay between actions or poses
// - Can be used for pacing, dramatic pauses, or synchronization
//
// ✅ Functionality:
// - Logs the wait event for debugging
// - Delays for a fixed 5 seconds
//
// ✅ Usage:
//     trait_wait();  // Inserts a 5-second pause in the motion sequence

void trait_wait() {
  Serial.println("Trait: Wait");
  delay(5000);  // Fixed pause duration
}

#endif