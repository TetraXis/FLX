#ifndef FLX_INC_CORE_HPP
#define FLX_INC_CORE_HPP

// This header sets up macros and detects all necessary stuff.

#define FLX_VERSION "0.0.0"
#define FLX_VERSION_MAJOR 0
#define FLX_VERSION_MINOR 0
#define FLX_VERSION_PATCH 0

// A brief list of options for building FLX:
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
// v.0.0.0 2026-Apr-14:
// core_cfg.hpp created.
// terminate.hpp created.
// assert.hpp created.
// core_has.hpp created.
//
// v.0.0.0 2026-Apr-13:
// core.hpp created.
// core_env.hpp created, necessary checks coded.
// core_opt.hpp created, necessary checks coded.



#include "flx/core_opt.hpp"

#include "flx/core_cfg.hpp"

#include "flx/core_has.hpp"

#include "flx/core_env.hpp"



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


#endif //FLX_INC_CORE_HPP