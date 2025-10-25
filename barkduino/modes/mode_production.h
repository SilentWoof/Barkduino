#ifndef MODE_PRODUCTION_H
#define MODE_PRODUCTION_H

#include <Arduino.h>
#include "../poses/pose_composites.h"
#include "../utils/trait_executor.h"
#include "../traits/trait_registry.h"

// 🧠 External flags
extern bool traitInProgress;
extern int lastTraitIndex;

void runProductionLoop() {
  if (traitInProgress) return;

  if (isTriggerDetected()) {
    Serial.println("Mode 1 — Production: Trigger detected.");
    poseStand(); delay(250);

    int traitCount = sizeof(traitRegistry) / sizeof(traitRegistry[0]);
    int selected;

    // 🔁 Retry until a different trait is selected
    do {
      selected = random(traitCount);
    } while (selected == lastTraitIndex && traitCount > 1);

    Serial.print("Selected trait ID "); Serial.println(selected);
    lastTraitIndex = selected;
    executeTrait(traitRegistry[selected]);
  }
}

#endif