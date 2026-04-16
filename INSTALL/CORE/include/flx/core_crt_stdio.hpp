#ifndef FLX_INC_CORE_CRT_STDIO_HPP
#define FLX_INC_CORE_CRT_STDIO_HPP

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

	i32 write(i32, const void*, u32);



	// ===== POSIX CRT ===== //
#else

	sszt write(i32, const void*, szt);



#endif
} // extern "C"

namespace flx::crt
{
	inline sszt write(const i32 fd, const void* buffer, const u32 count) // smaller input parameters are used to ensure Win CRT won't bug.
	{ return ::write(fd, buffer, count); }
} // namespace flx::crt



#endif //FLX_INC_CORE_CRT_STDIO_HPP