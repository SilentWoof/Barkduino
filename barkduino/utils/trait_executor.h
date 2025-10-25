#ifndef TRAIT_EXECUTOR_H
#define TRAIT_EXECUTOR_H

#include <Arduino.h>
#include "../poses/pose_composites.h"

// These flags must be declared in barkduino.ino
extern bool traitInProgress;
extern bool triggerLocked;
extern const unsigned long triggerCooldown;

// Trait function type
typedef void (*TraitFunction)();

// 🧠 Trait execution wrapper with cooldown enforcement
void executeTrait(TraitFunction trait) {
  traitInProgress = true;
  trait();              // Run the trait
  poseSleep();          // Return to sleep posture
  Serial.println("Trait complete. Enforcing cooldown...");
  delay(triggerCooldown);
  traitInProgress = false;
  triggerLocked = false;  // Require sensor to clear before next trigger
}

#endif