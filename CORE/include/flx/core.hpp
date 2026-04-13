#ifndef FLX_INC_CORE_HPP
#define FLX_INC_CORE_HPP

// This header sets up macros and detects all necessary stuff.

#define FLX_VERSION "0.0.0"
#define FLX_VERSION_MAJOR 0
#define FLX_VERSION_MINOR 0
#define FLX_VERSION_PATCH 0

// A brief list of options for building FLX:
// 1. Forcing build environment:
//		FLX_OPT_FORCE_COMPILER_*	- for forcing compiler
//		FLX_OPT_FORCE_ARCH_*		- for forcing architecture
//		FLX_OPT_FORCE_OS_*			- for forcing operating system
//		FLX_OPT_FORCE_CRT_*			- for forcing C Runtime

// Changelog:
//
// v.0.0.0 2026-Apr-13:
// core.hpp created.
// core_env.hpp created, necessary checks coded.
// core_opt.hpp created, necessary checks coded.

#include "flx/core_opt.hpp"

#include "flx/core_env.hpp"

#endif //FLX_INC_CORE_HPP