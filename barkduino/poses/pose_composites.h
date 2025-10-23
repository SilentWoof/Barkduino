#ifndef POSE_COMPOSITES_H
#define POSE_COMPOSITES_H

#include <Arduino.h>
#include "leg_primitives.h"

// 🎭 Composite Poses

void poseSleep() {
  Serial.println("Pose: Sleep");
  RearForward();       // Rear legs folded forward.
  delay(500);
  FrontBack();         // Front legs folded back
}

void poseStand() {
  Serial.println("Pose: Stand");
  FrontStraight();     // Front legs straight
  delay(500);
  RearStraight();      // Rear legs straight
}

void poseSit() {
  Serial.println("Pose: Sit");
  RearForward();       // Rear legs folded forward under the body
  delay(500);
  FrontStraight();     // Front legs upright for posture
}

void poseBow() {
  Serial.println("Pose: Bow");
  RearStraight();         // Rear legs stay upright
  delay(500);
  FrontBack();            // Front legs fold back to lower the front
}

void posePounce() {
  Serial.println("Pose: Pounce");
  RearMidwayBack();       // Rear legs crouched, ready to spring
  delay(500);
  FrontForward();         // Front legs extended forward
}

void poseSpread() {
  Serial.println("Pose: Spread");
  FrontForward();         // Front legs stretched forward
  delay(500);
  RearBack();             // Rear legs stretched backward
}

void posePoint() {
  Serial.println("Pose: Point");

  RearMidwayBack();       // Rear legs crouched, ready to spring
  delay(500);

  Serial.println("Front legs: asymmetrical point");
  front_left.write(60);   // Front left leg: straight
  front_right.write(0);   // Front right leg: forward
}

#endif