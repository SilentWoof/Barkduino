# Barkduino 🐾  
Modular Arduino-based quadruped robot with synchronized servo control, distance-triggered behaviors, and trait-driven personality.

## 🧠 Overview

Barkduino is a compact, expressive robot designed for modular behavior orchestration. It uses synchronized servo sweeps to animate leg poses, distance sensing for trigger detection, and a trait registry for expandable personality actions. The codebase is fully modular, enabling clean onboarding, testing, and expansion.

## 📁 Project Structure

barkduino/
├── barkduino.ino           # Main orchestration logic
├── traits/                 # Modular trait definitions
│   ├── trait_bow.h
│   ├── trait_point_left.h
│   ├── ...
│   └── trait_registry.h    # Centralized trait list
├── poses/                  # Leg pose definitions
│   ├── leg_primitives.h    # Low-level leg movements
│   └── pose_composites.h   # Full-body poses
├── modes/                  # Behavior modes
│   ├── mode_production.h
│   ├── mode_trait_test.h
│   ├── mode_calibration.h
│   └── (uses diagnostics.h for waggle mode)
├── utils/                  # Shared utilities
│   ├── trait_executor.h
│   ├── trigger_logic.h
│   ├── servo_utils.h
│   └── diagnostics.h
├── configs/                # Timing and motion constants
│   └── motion_config.h
├── docs/                   # Documentation and design notes
├── hardware/               # Wiring diagrams, calibration data, etc.

## 🚦 Modes

Set ACTIVE_MODE in barkduino.ino to control behavior:

| Mode Name     | Constant        | Description                          |
|---------------|-----------------|--------------------------------------|
| Production     | MODE_1          | Triggered loop with random trait     |
| Trait Testing  | MODE_2          | Triggered loop with selected trait   |
| Calibration    | MODE_3          | Static standing pose for tuning      |
| Waggle Test    | MODE_4          | Cycles each leg for servo check      |

## 🎭 Poses

Defined in poses/ and used across modes:

- Primitives: rearLegsFoldedForward(), rearLegsStraight(), frontLegsFoldedBack(), frontLegsStraight()
- Composites: poseSleep(), poseStand()

## 🎬 Traits

Defined in traits/ and registered in trait_registry.h. Each trait is a standalone function (e.g. trait_wait()) and can be randomly selected or manually triggered.

## 🧩 Expansion

To add a new trait:
1. Create a new file in traits/ (e.g. trait_wave.h)
2. Define the trait function:
   void trait_wave() {
     // Your behavior here
   }
3. Add it to traitRegistry[] in trait_registry.h

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
   git clone https://github.com/SilentWoof/Barkduino.git
2. Open barkduino/barkduino.ino in Arduino IDE
3. Upload to your board

## 📚 License

Barkduino License

Copyright (c) 2025 James Starling

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to use,
copy, modify, and distribute the Software for personal, educational, or research
purposes, subject to the following conditions:

1. Non-Commercial Use:
   The Software may not be used, in whole or in part, for commercial purposes
   without prior written permission from the copyright holder. This includes,
   but is not limited to, selling the Software, using it in commercial products,
   or integrating it into services or platforms that generate revenue.

2. Attribution:
   Any redistribution of the Software must retain the above copyright notice,
   this license text, and any original documentation provided with the Software.

3. Modifications:
   You may modify the Software for personal or educational use. Modified versions
   must clearly indicate changes and must not be misrepresented as the original
   work.

4. No Warranty:
   The Software is provided "as is", without warranty of any kind, express or
   implied, including but not limited to the warranties of merchantability,
   fitness for a particular purpose, and noninfringement. In no event shall the
   author be liable for any claim, damages, or other liability arising from the
   use of the Software.

5. Commercial Licensing:
   For commercial licensing inquiries, please contact:
   james.starling.robotics@gmail.com

This license is governed by and construed in accordance with the laws of Ireland.