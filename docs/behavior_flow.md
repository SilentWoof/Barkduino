# Barkduino Behavior Flow 🧠

This document outlines the runtime behavior of Barkduino across its operational modes, detailing how triggers are detected, poses are sequenced, and traits are executed.

## 🚦 Mode Selection

Behavior is determined by the ACTIVE_MODE constant in barkduino.ino. Available modes:

| Mode Name     | Constant           | Description                        |
|---------------|--------------------|------------------------------------|
| Production     | MODE_PRODUCTION    | Triggered loop with random trait   |
| Trait Testing  | MODE_TRAIT_TEST    | Triggered loop with selected trait |
| Calibration    | MODE_CALIBRATION   | Static standing pose for tuning    |
| Waggle Test    | MODE_WAGGLE_TEST   | Cycles each leg for servo check    |

## 📡 Trigger Detection

Triggering is based on proximity using an HC-SR04 ultrasonic sensor:

- getDistanceCM() measures distance in cm.
- isTriggerDetected() returns true if distance is between 0 and 20 cm.

This detection is polled inside each mode loop.

## 🧩 Pose Sequencing

All modes (except Waggle Test) begin with:

1. poseSleeping() — rear legs folded forward, front legs folded back
2. poseStanding() — front legs straight, rear legs straight

These are defined in pose_composites.h and built from primitives in leg_primitives.h.

## 🎬 Trait Execution

### Trait Registry

Traits are modular functions registered in:

TraitFunction traitRegistry[] = {
  trait_wait,
  // Add more traits here
};

### Execution Flow

- Production Mode:
  - Random trait selected from traitRegistry[]
  - Executed after pose transition

- Trait Testing Mode:
  - Executes trait at index SELECTED_TRAIT
  - Useful for verifying individual behaviors

## 🧠 Loop Flow Summary

### Production Mode

if (trigger detected) {
  poseSleeping();
  poseStanding();
  select random trait;
  execute trait;
  poseSleeping();
}

### Trait Testing Mode

if (trigger detected) {
  poseSleeping();
  poseStanding();
  execute SELECTED_TRAIT;
  poseSleeping();
}

### Calibration Mode

poseStanding(); // static pose for tuning

### Waggle Test Mode

poseStanding();
waggle each leg for 3 seconds;
halt;

## 🧩 Expansion Notes

- Add new traits in traits/ and register in traitRegistry[]
- Add new poses by combining primitives in pose_composites.h
- All behavior is modular and easily testable via mode selection

## 📚 Related Files

- barkduino.ino — main orchestration logic
- traits/ — trait definitions
- poses/leg_primitives.h — low-level leg positions
- poses/pose_composites.h — high-level pose sequences