#ifndef FLX_INC_ASSERT_HPP
#define FLX_INC_ASSERT_HPP

// This header defines assert function.
// CAUTION! This header links to flx::terminate and CRT::write only in DEBUG

#include "flx/core.hpp"

#if FLX_CFG_DEBUG // in RELEASE this header should be a husk.

#include "flx/terminate.hpp"

// ===== FLX_CRT_WRITE for ASSERT ===== //

#if !defined(FLX_CRT_WRITE)
extern "C"
{
#if FLX_ENV_CRT == FLX_ENV_CRT_UCRT || FLX_ENV_CRT_MSVCRT
	int _write(int fd, const void* buffer, unsigned int count);
	#define FLX_CRT_WRITE ::_write
#else
	long write(int fd, const void* buf, unsigned long count);
	#define FLX_CRT_WRITE ::write
#endif
}
#endif //FLX_CFG_DEBUG && !defined(FLX_CRT_WRITE)



// ===== ASSERT ===== //

namespace flx
{
	inline void assert(const bool condition, const c8* msg) noexcept
	{
		if (!condition)
		{
			FLX_CRT_WRITE(2, msg, static_cast<unsigned int>(sizeof(msg) - 1));
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