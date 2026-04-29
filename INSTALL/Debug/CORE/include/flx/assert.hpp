#ifndef FLX_INC_ASSERT_HPP
#define FLX_INC_ASSERT_HPP

// This header defines assert function.
// CAUTION! This header links to flx::terminate and CRT only in DEBUG

#include "flx/core.hpp"

#if FLX_CFG_DEBUG // in RELEASE this header should be a husk.

#include "flx/terminate.hpp"

// ===== ASSERT ===== //

namespace flx
{
	inline void assert(const bool condition, const c8* msg) noexcept
	{
		if (!condition)
		{
			::flx::crt::write(2, msg, ::flx::crt::strlen(msg));
			::flx::terminate();
		}
	}
} // namespace flx

#else // We are in RELEASE.

namespace flx
{
	inline void assert([[maybe_unused]] bool condition, [[maybe_unused]] const c8* msg) noexcept
	{
	}
} // namespace flx

#endif //FLX_CFG_DEBUG



#endif //FLX_INC_ASSERT_HPP