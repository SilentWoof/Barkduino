#ifndef POSE_COMPOSITES_H
#define POSE_COMPOSITES_H

#include <Arduino.h>
#include "leg_primitives.h"

// 🎭 Composite Poses
// Sleep and Stand are static poses called and always used in the main loop and training loop.
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

// The following poses are called in traits and behaviors.

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
  front_left.write(0);    // Front left leg: forward (matches FrontForward left)
  front_right.write(110); // Front right leg: straight (matches FrontStraight right)
}

#endif