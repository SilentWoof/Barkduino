#ifndef MODE_PRODUCTION_H
#define MODE_PRODUCTION_H

#include <Arduino.h>
#include "../poses/pose_composites.h"
#include "../utils/trait_executor.h"
#include "../traits/trait_registry.h"

// 🧠 External flags
extern bool traitInProgress;

// 🎭 Mode 1: Random trait execution
void runProductionLoop() {
  if (traitInProgress) return;

  if (isTriggerDetected()) {
    Serial.println("Mode 1 — Production: Trigger detected.");
    poseStand(); delay(250);

    int selected = random(sizeof(traitRegistry) / sizeof(traitRegistry[0]));
    Serial.print("Selected trait ID "); Serial.println(selected);
    executeTrait(traitRegistry[selected]);
  }
}

#endif