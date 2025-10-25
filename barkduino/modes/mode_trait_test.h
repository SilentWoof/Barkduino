#ifndef MODE_TRAIT_TEST_H
#define MODE_TRAIT_TEST_H

#include <Arduino.h>
#include "../poses/pose_composites.h"
#include "../utils/trait_executor.h"
#include "../traits/trait_registry.h"

// 🧠 External flags and constants
extern bool traitInProgress;
extern const int SELECTED_TRAIT;

// 🎭 Mode 2: Execute selected trait
void runTraitTestingLoop() {
  if (traitInProgress) return;

  if (isTriggerDetected()) {
    Serial.println("Mode 2 — Trait Testing: Trigger detected.");
    poseStand();

    int traitCount = sizeof(traitRegistry) / sizeof(traitRegistry[0]);
    if (SELECTED_TRAIT >= 0 && SELECTED_TRAIT < traitCount) {
      Serial.print("Selected trait ID "); Serial.println(SELECTED_TRAIT);
      executeTrait(traitRegistry[SELECTED_TRAIT]);
    } else {
      Serial.println("Invalid trait ID.");
    }
  }
}

#endif