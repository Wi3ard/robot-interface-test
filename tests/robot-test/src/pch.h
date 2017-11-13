#pragma once

#ifndef STRICT
#define STRICT
#endif

#ifdef WIN32

#include "targetver.h"

#ifdef NDEBUG

// Turn on intrinsics.
#include <intrin.h>

#endif  // #ifdef NDEBUG

#endif  // #ifdef WIN32

//////////////////////////////////////////////////////////////////////////
// STL includes and definitions.
//

#include <memory>
#include <random>

//////////////////////////////////////////////////////////////////////////
// Google Test includes and definitions.
//

#include <gtest/gtest.h>

//////////////////////////////////////////////////////////////////////////
// robot-sdk library.
//

#include <robot-sdk/IRobot.h>
