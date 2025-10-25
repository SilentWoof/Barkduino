#ifndef MODE_PRODUCTION_H
#define MODE_PRODUCTION_H

#include <Arduino.h>
#include "../poses/pose_composites.h"
#include "../utils/trait_executor.h"
#include "../traits/trait_registry.h"

// 🧠 External flags
extern bool traitInProgress;

// 🧠 Local history buffer for last 3 traits
const int TRAIT_HISTORY_SIZE = 3;
int recentTraits[TRAIT_HISTORY_SIZE] = { -1, -1, -1 };
int traitHistoryIndex = 0;

bool isRecentlyUsed(int index) {
  for (int i = 0; i < TRAIT_HISTORY_SIZE; i++) {
    if (recentTraits[i] == index) return true;
  }
  return false;
}

void rememberTrait(int index) {
  recentTraits[traitHistoryIndex] = index;
  traitHistoryIndex = (traitHistoryIndex + 1) % TRAIT_HISTORY_SIZE;
}

void runProductionLoop() {
  if (traitInProgress) return;

  if (isTriggerDetected()) {
    Serial.println("Mode 1 — Production: Trigger detected.");
    poseStand(); delay(DEFAULT_SYNC_DURATION);

    int traitCount = sizeof(traitRegistry) / sizeof(traitRegistry[0]);
    int selected;

    // 🔁 Retry until a trait not in recent history is selected
    int attempts = 0;
    do {
      selected = random(traitCount);
      attempts++;
    } while (isRecentlyUsed(selected) && attempts < 10);

    Serial.print("Selected trait ID "); Serial.println(selected);
    rememberTrait(selected);
    executeTrait(traitRegistry[selected]);
  }
}

#endif