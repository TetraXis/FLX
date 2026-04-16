#ifndef FLX_INC_CORE_HAS_HPP
#define FLX_INC_CORE_HAS_HPP

// This header detects accessible features.

// To Dev: This header should be updated when new C++ features are used across the FLX.
// Or when full C++26 support arrives.

#include "flx/core_opt.hpp"
#include "flx/core_env.hpp"

// ===== C++26 ===== //

#define FLX_HAS_CXX26 (FLX_ENV_CXX_LANG >= 202400L)

#if !FLX_HAS_CXX26
	#error "Unsupported C++ Standard. FLX requires C++26 or higher."
#endif // !FLX_HAS_CXX26



#endif //FLX_INC_CORE_HAS_HPP