#pragma once

#ifndef STRICT
#define STRICT
#endif

#ifdef WIN32

#include "targetver.h"

#ifdef NDEBUG

// Turn on intrinsics.
#include <intrin.h>

#endif	// #ifdef NDEBUG

#endif	// #ifdef WIN32
