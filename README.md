# Barkduino 🐾  
Modular Arduino-based quadruped robot with synchronized servo control, distance-triggered behaviors, and trait-driven personality.

## 🧠 Overview

Barkduino is a compact, expressive robot designed for modular behavior orchestration. It uses synchronized servo sweeps to animate leg poses, distance sensing for trigger detection, and a trait registry for expandable personality actions.

## 📁 Project Structure

Barkduino/
├── barkduino/              # Main Arduino sketch folder
│   ├── barkduino.ino       # Core orchestration logic
│   ├── traits/             # Modular trait definitions
│   │   └── trait_wait.h
│   ├── poses/              # Leg pose definitions
│   │   ├── leg_primitives.h
│   │   └── pose_composites.h
├── docs/                   # Documentation and design notes
├── hardware/               # Wiring diagrams, calibration data, etc.

## 🚦 Modes

Set ACTIVE_MODE in barkduino.ino to control behavior:

| Mode Name     | Constant           | Description                        |
|---------------|--------------------|------------------------------------|
| Production     | MODE_PRODUCTION    | Triggered loop with random trait   |
| Trait Testing  | MODE_TRAIT_TEST    | Triggered loop with selected trait |
| Calibration    | MODE_CALIBRATION   | Static standing pose for tuning    |
| Waggle Test    | MODE_WAGGLE_TEST   | Cycles each leg for servo check    |

## 🎭 Poses

Defined in poses/ and used across modes:

- Primitives: rearLegsFoldedForward(), rearLegsStraight(), frontLegsFoldedBack(), frontLegsStraight()
- Composites: poseSleeping(), poseStanding()

## 🎬 Traits

Defined in traits/ and registered in traitRegistry[]. Each trait is a standalone function (e.g. trait_wait()) and can be randomly selected or manually triggered.

## 🧩 Expansion

To add a new trait:
1. Create a new file in traits/ (e.g. trait_wave.h)
2. Define the trait function:
   void trait_wave() {
     // Your behavior here
   }
3. Add it to traitRegistry[] in barkduino.ino

To add a new pose:
1. Define primitives in leg_primitives.h
2. Combine them in pose_composites.h

## 🛠 Requirements

- Arduino-compatible board (e.g. Nano, Uno)
- 4x servo motors
- HC-SR04 ultrasonic sensor
- Arduino IDE or CLI

## 📦 Setup

1. Clone the repo:
   git clone https://github.com/yourusername/Barkduino.git
2. Open barkduino/barkduino.ino in Arduino IDE
3. Upload to your board

## 📚 License

MIT License. See LICENSE for details.