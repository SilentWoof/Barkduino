#ifndef TRIGGER_LOGIC_H
#define TRIGGER_LOGIC_H

#include <Arduino.h>

// These flags and constants must be declared in barkduino.ino
extern bool triggerLocked;
extern bool traitInProgress;
extern unsigned long lastTriggerTime;
extern const unsigned long triggerCooldown;

// 📏 Distance sensor pins (must match barkduino.ino)
const int trigPin = 5;
const int echoPin = 4;

// 📏 Distance measurement
long getDistanceCM() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  return duration * 0.034 / 2;
}

// 🚨 Unified trigger detection
bool isTriggerDetected() {
  long distance = getDistanceCM();
  unsigned long now = millis();

  if (distance > 0 && distance < 20) {
    if (!triggerLocked && !traitInProgress) {
      lastTriggerTime = now;
      triggerLocked = true;
      Serial.print("Sensor reading: ");
      Serial.print(distance);
      Serial.println(" cm — Trigger accepted");
      return true;
    }
  } else {
    if (triggerLocked) Serial.println("Sensor clear — trigger unlocked");
    triggerLocked = false;
  }

  return false;
}

#endif