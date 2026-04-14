#ifndef FLX_INC_CORE_CFG_HPP
#define FLX_INC_CORE_CFG_HPP

// This header defines and checks configuration for building FLX.

#include "flx/core_opt.hpp"

// ===== DEBUG/RELEASE ===== //

#if defined(FLX_OPT_FORCE_DEBUG)
	#define FLX_CFG_RELEASE	false
	#define FLX_CFG_DEBUG	true
#elif defined(FLX_OPT_FORCE_DEBUG)
	#define FLX_CFG_RELEASE	true
	#define FLX_CFG_DEBUG	false
#else
	#define FLX_CFG_RELEASE	true
	#define FLX_CFG_DEBUG	false
#endif



#endif //FLX_INC_CORE_CFG_HPP