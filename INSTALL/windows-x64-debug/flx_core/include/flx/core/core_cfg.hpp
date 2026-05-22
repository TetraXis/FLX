#ifndef FLX_INC_CORE_CFG_HPP
#define FLX_INC_CORE_CFG_HPP

// This header defines and checks configuration for building FLX.
// All CFG macros can be true or false.

#include "flx/core/core_opt.hpp"

// ===== DEBUG/RELEASE ===== //

#if defined(FLX_OPT_FORCE_DEBUG)
	#define FLX_CFG_RELEASE	false
	#define FLX_CFG_DEBUG	true
#elif defined(FLX_OPT_FORCE_RELEASE)
	#define FLX_CFG_RELEASE	true
	#define FLX_CFG_DEBUG	false
#else
	#if defined(FLX_OPT_DEBUG)
		#define FLX_CFG_RELEASE	false
		#define FLX_CFG_DEBUG	true
	#elif defined(FLX_OPT_RELEASE)
		#define FLX_CFG_RELEASE	true
		#define FLX_CFG_DEBUG	false
	#else
		#define FLX_CFG_RELEASE	true
		#define FLX_CFG_DEBUG	false
	#endif
#endif



// ===== TRACE ===== //

#if defined(FLX_OPT_FORCE_TRACE) || FLX_CFG_DEBUG
	#define FLX_CFG_USE_TRACE true
#else
	#define FLX_CFG_USE_TRACE false
#endif



#endif //FLX_INC_CORE_CFG_HPP