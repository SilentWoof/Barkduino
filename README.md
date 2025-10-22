# Barkduino 🐾

**Barkduino** is a behavior-driven robot companion built on Arduino. It mimics dog-like gestures and emotional feedback—but looks nothing like a dog. Designed for expressive motion, modular traits, and creative form.

## Features
- 🐶 Dog-inspired behavior (sleep, stand, waggle, wait)
- 🎭 Modular trait system
- 🧠 Mode-based logic (Production, Trait Testing, Calibration, Waggle Test)
- 🔧 Servo synchronization and gesture primitives
- 🦴 Ultrasonic trigger detection

## Modes
| Mode | Description |
|------|-------------|
| 1    | Production: sleep → stand → random trait → sleep |
| 2    | Trait Testing: sleep → stand → selected trait → sleep |
| 3    | Calibration: hold standing pose |
| 4    | Waggle Test: stand → waggle each leg for 3s |

## Traits
- `wait`: pauses for 2 seconds

## Getting Started
1. Upload `barkduino.ino` to your Arduino board
2. Connect 4 servos and an ultrasonic sensor (TRIG on D4, ECHO on D5)
3. Open Serial Monitor at 9600 baud
4. Trigger with hand movement < 20cm

## License
MIT or CC-BY-SA recommended—your call!
