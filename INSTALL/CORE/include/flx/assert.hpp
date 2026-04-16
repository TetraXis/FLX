#ifndef FLX_INC_ASSERT_HPP
#define FLX_INC_ASSERT_HPP

// This header defines assert function.
// CAUTION! This header links to flx::terminate and CRT only in DEBUG

#include "flx/core.hpp"

#if FLX_CFG_DEBUG // in RELEASE this header should be a husk.

#include "flx/core_crt.hpp"
#include "flx/terminate.hpp"

// ===== FLX_CRT_WRITE ===== //

/*#if !defined(FLX_CRT_WRITE)
extern "C"
{
	using namespace ::flx::types;

#if FLX_ENV_CRT == FLX_ENV_CRT_UCRT || FLX_ENV_CRT == FLX_ENV_CRT_MSVCRT
	i32 _write(i32 fd, const void* buffer, u32 count);
	#define FLX_CRT_WRITE(fd, buffer, count) \
	::_write(static_cast<i32>(fd), static_cast<const void*>(buffer), static_cast<u32>(count))
#else
	sszt write(i32 fd, const void* buf, szt count);
	#define FLX_CRT_WRITE(fd, buffer, count) \
	::write(static_cast<i32>(fd), static_cast<const void*>(buffer), static_cast<szt>(count))
#endif
}
#endif // !defined(FLX_CRT_WRITE)



// ===== FLX_CRT_STRLEN ===== //

#if !defined(FLX_CRT_STRLEN)
extern "C"
{
	using namespace ::flx::types;

	szt strlen(const c8*);
	#define FLX_CRT_STRLEN(buffer) \
	::strlen(static_cast<const c8*>(buffer))
}
#endif // !defined(FLX_CRT_WRITE)*/



// ===== ASSERT ===== //

namespace flx
{
	inline void assert(const bool condition, const c8* msg) noexcept
	{
		if (!condition)
		{
			//FLX_CRT_WRITE(2, msg, FLX_CRT_STRLEN(msg));
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