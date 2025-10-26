#ifndef MODE_CYCLE_PRIMITIVES_H
#define MODE_CYCLE_PRIMITIVES_H

#include <Arduino.h>
#include "../utils/motion_config.h"
#include "../poses/leg_primitives.h"
#include "../utils/servo_utils.h"

// 🌀 Mode 5: Auto-cycle through synchronized leg primitives
void runPrimitiveCycleMode() {
  Serial.println("Mode 5 — Auto-Cycling Leg Positions");
  Serial.println("Cycling through 5 primitive poses every 2.5 seconds...");

  void (*positionPairs[])(int) = {
    [](int d) { FrontForward(d);       RearForward(d);       },
    [](int d) { FrontMidwayForward(d); RearMidwayForward(d); },
    [](int d) { FrontStraight(d);      RearStraight(d);       },
    [](int d) { FrontMidwayBack(d);    RearMidwayBack(d);     },
    [](int d) { FrontBack(d);          RearBack(d);           }
  };

  const char* positionNames[] = {
    "Folded Forward",
    "Midway Forward",
    "Straight",
    "Midway Back",
    "Folded Back"
  };

  const int positionCount = sizeof(positionPairs) / sizeof(positionPairs[0]);
  int currentPosition = 0;

  while (true) {
    Serial.print("⏭️ Executing position #");
    Serial.print(currentPosition + 1);
    Serial.print(": ");
    Serial.println(positionNames[currentPosition]);

    positionPairs[currentPosition](DEFAULT_SYNC_DURATION);
    currentPosition = (currentPosition + 1) % positionCount;

    delay(2500);
  }
}

#endif