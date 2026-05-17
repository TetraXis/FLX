#ifndef FLX_INC_CORE_HPP
#define FLX_INC_CORE_HPP

// This header sets up macros and detects all necessary stuff.
// IMPORTANT NOTE:
// FLX treats moved-from objects as DEAD (relocated-from).
// FLX will NOT call destructors on them, and won't use them without creating new objects in their place.

#define FLX_VERSION "0.0.2"
#define FLX_VERSION_MAJOR 0
#define FLX_VERSION_MINOR 0
#define FLX_VERSION_PATCH 2

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

// Changelog:
//
// v.0.0.2 2026-May-07+:
// Added new.hpp
// Added core_error.hpp
//
// v.0.0.1 2026-May-01+:
// Switched from modules to headers.
//
// v.0.0.1 2026-Apr-20+:
// type_traits.hpp created.
// utility.hpp created.
//
// v.0.0.0 2026-Apr-13+:
// core.hpp created.
// core_env.hpp created, necessary checks coded.
// core_opt.hpp created, necessary checks coded.
// core_cfg.hpp created.
// terminate.hpp created.
// assert.hpp created.
// core_has.hpp created.
// core_crt.hpp created.
// flx/core_crt_assert.hpp created.
// flx/core_crt_complex.hpp created.
// flx/core_crt_ctype.hpp created.
// flx/core_crt_errno.hpp created.
// flx/core_crt_fenv.hpp created.
// flx/core_crt_float.hpp created.
// flx/core_crt_inttypes.hpp created.
// flx/core_crt_iso646.hpp created.
// flx/core_crt_limits.hpp created.
// flx/core_crt_locale.hpp created.
// flx/core_crt_math.hpp created.
// flx/core_crt_setjmp.hpp created.
// flx/core_crt_signal.hpp created.
// flx/core_crt_stdbool.hpp created.
// flx/core_crt_stddef.hpp created.
// flx/core_crt_stdint.hpp created.
// flx/core_crt_stdio.hpp created.
// flx/core_crt_stdlib.hpp created.
// flx/core_crt_string.hpp created.
// flx/core_crt_tgmath.hpp created.
// flx/core_crt_time.hpp created.
// flx/core_crt_wchar.hpp created.
// flx/core_crt_wctype.hpp created.



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
	using c8	= char;
	using c08	= char;
	using c16	= char16_t;
	using c32	= char32_t;
	using i8	= signed char;
	using i08	= signed char;
	using i16	= short;
	using i32	= int;
	using i64	= long long;
	using u8	= unsigned char;
	using u08	= unsigned char;
	using u16	= unsigned short;
	using u32	= unsigned int;
	using u64	= unsigned long long;
	using f32	= float;
	using f64	= double;
	using f80	= long double;

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

	constexpr ::flx::imp::tag_use_flx use_flx{};
} // namespace flx


#include "flx/core/core_opt.hpp"

#include "flx/core/core_cfg.hpp"

#include "flx/core/core_has.hpp"

#include "flx/core/core_env.hpp"

#include "flx/core/core_crt.hpp"



// deprecated until reflections are fully supported
// #include "flx/core/core_error.hpp"



#endif //FLX_INC_CORE_HPP