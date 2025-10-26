#ifndef MOTION_SPEED_PRESETS_H
#define MOTION_SPEED_PRESETS_H

// 🐾 Motion Speed Presets for Barkduino
//
// These named constants define optional speed overrides for servo motion.
// If no preset is passed to a primitive or trait, the system defaults to
// DEFAULT_SYNC_DURATION (defined in motion_config.h).
//
// Use these presets to fine-tune expressive timing per trait or action.
// Smaller values = faster motion. Larger values = slower, more deliberate motion.

const int VERY_FAST = 2;    // ⚡ Rapid snap motion
const int FAST      = 5;    // 🏃 Quick but readable
const int STANDARD  = 10;   // 🎯 Typical gesture speed
const int SLOW      = 20;   // 🐢 Expressive or cautious
const int DEAD_SLOW = 40;   // 🧘 Dramatic or theatrical

// 🎚️ Optional step size overrides (default is 5 degrees per step)
// Use these to control motion granularity independently of speed.
// Smaller step size = smoother motion with more steps.
// Larger step size = chunkier motion with fewer steps.

const int STEP_FINE     = 2;   // Smooth, high-resolution motion
const int STEP_STANDARD = 5;   // Default granularity
const int STEP_CHUNKY   = 10;  // Fast, low-resolution motion

#endif