#ifndef FLX_INC_CORE_HPP
#define FLX_INC_CORE_HPP

// This header sets up macros and detects all necessary stuff.
// IMPORTANT NOTE:
// FLX treats moved-from objects as DEAD (relocated-from).
// FLX will NOT call destructors on them, and won't use them without creating new objects in their place.

#define FLX_VERSION "0.0.3"
#define FLX_VERSION_MAJOR 0
#define FLX_VERSION_MINOR 0
#define FLX_VERSION_PATCH 3

// A brief list of options for building FLX:
// 0. Choosing configuration:
//		FLX_OPT_DEBUG				- for choosing debug mode
//		FLX_OPT_RELEASE				- for choosing release mode
// 1. Forcing configuration:
//		FLX_OPT_FORCE_DEBUG			- for forcing debug mode
//		FLX_OPT_FORCE_RELEASE		- for forcing release mode
// 2. Forcing all class members to be public:
//		FLX_OPT_FORCE_PUBLIC_MEMBERS
// 3. Forcing build environment:
//		FLX_OPT_FORCE_COMPILER_*	- for forcing compiler			(GCC, MSVC, CLANG, ...)
//		FLX_OPT_FORCE_ARCH_*		- for forcing architecture		(X86_32, X86_64, ARM_32, ARM_64)
//		FLX_OPT_FORCE_OS_*			- for forcing operating system	(WINDOWS, LINUX, APPLE, ...)
//		FLX_OPT_FORCE_CRT_*			- for forcing C Runtime			(UCRT, MSVCRT, GLIBC, MUSL, ...)
// 4. Trace settings
//		FLX_OPT_FORCE_TRACE			- for forcing use of trace	(by default it is only active in DEBUG)
//		FLX_OPT_TRACE_DEPTH			- for setting trace depth	(default is 32)



#ifdef FLX_OPT_FORCE_PUBLIC_MEMBERS
	#define flx_public		public
	#define flx_protected	public
	#define flx_private		public
#else
	#define flx_public		public
	#define flx_protected	protected
	#define flx_private		private
#endif // FLX_OPT_FORCE_PUBLIC_MEMBERS

namespace flx::inline types
{
	using u0	= void;
	using u00	= void;
	using b8	= bool;
	using b08	= bool;
	using c8	= char8_t;
	using c08	= char8_t;
	using c16	= char16_t;
	using c32	= char32_t;
	using i8	= signed char;		// no way to guarantee 8 bits
	using i08	= signed char;		// no way to guarantee 8 bits
	using i16	= signed short;
	using i32	= signed int;
	using i64	= signed long long;
	using u8	= unsigned char;	// no way to guarantee 8 bits
	using u08	= unsigned char;	// no way to guarantee 8 bits
	using u16	= unsigned short;	
	using u32	= unsigned int;
	using u64	= unsigned long long;
	using f32	= float;
	using f64	= double;
	using f80	= long double;

	using chr	= char;
	using wct	= wchar_t;
	using szt	= decltype(sizeof nullptr);
	using sszt	= decltype(static_cast<char*>(nullptr) - static_cast<char*>(nullptr));
} // namespace flx::inline types

namespace flx
{
	namespace imp
	{
		struct tag_use_flx
		{
			explicit tag_use_flx() = default;
		};
	}

	inline constexpr ::flx::imp::tag_use_flx use_flx{};
} // namespace flx

// This defines custom placement news for FLX.
// The problem is: other headers already define this placement new, so conflicts arise
// operator new can only be global or class specific
// Forcing all types to implement placement new is bad
// MSVC doesn't have weak linking, so we need entirely unique placement new
// Custom tag 'use_flx' is therefore used.
// Since operator new can only be global, there is no point of making this a module.

constexpr void* operator new ([[maybe_unused]] ::flx::szt, void* ptr, [[maybe_unused]] ::flx::imp::tag_use_flx) noexcept
{
	return ptr;
}

constexpr void* operator new[]([[maybe_unused]] ::flx::szt, void* ptr, [[maybe_unused]] ::flx::imp::tag_use_flx) noexcept
{
	return ptr;
}

#include "flx/core/core_opt.hpp"

#include "flx/core/core_cfg.hpp"

#include "flx/core/core_has.hpp"

#include "flx/core/core_env.hpp"

#include "flx/core/core_crt.hpp"



// deprecated until reflections are fully supported
// #include "flx/core/core_error.hpp"



#endif //FLX_INC_CORE_HPP