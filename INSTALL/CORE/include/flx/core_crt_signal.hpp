#ifndef FLX_INC_CORE_CRT_SIGNAL_HPP
#define FLX_INC_CORE_CRT_SIGNAL_HPP

// This is a part of a compatibility layer between FLX and CRT.
// It is needed since Windows' CRT does not follow POSIX.

// To Dev: when linking to new CRT functions, do not forget to add both variants.

#include  "flx/core.hpp"

extern "C"
{
	using namespace flx::types;

	// ===== SAME CRT ===== //





	// ===== WIN CRT ===== //
#if FLX_ENV_CRT == FLX_ENV_CRT_MSVCRT || FLX_ENV_CRT == FLX_ENV_CRT_UCRT





	// ===== POSIX CRT ===== //
#else





#endif
} // extern "C"

namespace flx::crt
{

} // namespace flx::crt



#endif //FLX_INC_CORE_CRT_SIGNAL_HPP