#ifndef FLX_INC_TERMINATE_HPP
#define FLX_INC_TERMINATE_HPP

// This header defines terminate behavior.
// You can assign new functionality to 'flx::on_terminate'.

#include "flx/core.hpp"

namespace flx
{
	inline thread_local void (*on_terminate) () noexcept =
	+[]() noexcept
	{
	};

	[[noreturn]] inline void terminate() noexcept
	{
		::flx::on_terminate();

#if FLX_ENV_COMPILER == FLX_ENV_COMPILER_GCC || FLX_ENV_COMPILER == FLX_ENV_COMPILER_CLANG
		__builtin_trap();
#elif FLX_ENV_COMPILER == FLX_ENV_COMPILER_MSVC
		__debugbreak();
#else
#warning "Unknown compiler. Use your intrinsic for a program trap."
		volatile auto* p = (szt*)(nullptr);
		*p = 0;
#endif
	}
} // namespace flx

#endif //FLX_INC_TERMINATE_HPP