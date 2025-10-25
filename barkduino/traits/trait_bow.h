#ifndef TRAIT_BOW_H
#define TRAIT_BOW_H

#include <Arduino.h>
#include "../poses/leg_primitives.h"

void trait_bow() {
  const int slow = 40;  // Slower movement speed

  Serial.println("Trait: Bow");

  RearStraight(slow);
  FrontBack(slow);
  delay(500);
  FrontStraight(slow);
  delay(250);
  RearForward(slow);
}
#endif