#ifndef FLX_INC_CORE_HPP
#define FLX_INC_CORE_HPP

// This header sets up macros and detects all necessary stuff.

#define FLX_VERSION "0.0.0"
#define FLX_VERSION_MAJOR 0
#define FLX_VERSION_MINOR 0
#define FLX_VERSION_PATCH 0

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
//		FLX_OPT_FORCE_COMPILER_*	- for forcing compiler
//		FLX_OPT_FORCE_ARCH_*		- for forcing architecture
//		FLX_OPT_FORCE_OS_*			- for forcing operating system
//		FLX_OPT_FORCE_CRT_*			- for forcing C Runtime

// Changelog:
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


#include "flx/core_opt.hpp"

#include "flx/core_cfg.hpp"

#include "flx/core_has.hpp"

#include "flx/core_env.hpp"

#include "flx/core_crt.hpp"



#endif //FLX_INC_CORE_HPP