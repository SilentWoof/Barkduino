#ifndef TRAIT_REGISTRY_H
#define TRAIT_REGISTRY_H

#include "trait_bow.h"
#include "trait_point_left.h"
#include "trait_point_right.h"
#include "trait_pounce.h"
#include "trait_sit.h"
#include "trait_spread.h"
#include "trait_wait.h"

// 🧠 Trait registry for modular behavior selection
typedef void (*TraitFunction)();

TraitFunction traitRegistry[] = {
  trait_bow,         // 0
  trait_point_left,  // 1
  trait_point_right, // 2
  trait_pounce,      // 3
  trait_sit,         // 4
  trait_spread,      // 5
  trait_wait         // 6
};

#endif