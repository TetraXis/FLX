module;

// This module defines terminate behavior.
// You can assign new functionality to 'flx::on_terminate'.

#include "flx/core.hpp"

export module flx.terminate;

export namespace flx
{
	// TODO: think about thread_local
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

	[[noreturn]] inline void terminate(const char* msg) noexcept
	{
		::flx::on_terminate();

		::flx::crt::write(2, msg, ::flx::crt::strlen(msg));

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