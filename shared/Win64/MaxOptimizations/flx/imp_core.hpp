#ifndef IMP_FLX_IMP_CORE_HPP_
#define IMP_FLX_IMP_CORE_HPP_

/// ====== Main header for internals ====== ///
// Settings:
// FLX_ALL_MEMBERS_ARE_PUBLIC:	Define if you need all class members to become public.
// FLX_BUILDING_SHARED:			Define when building FLX as a dynamic library. (unchecked functionality)
// FLX_USING_SHARED:			Define when using FLX as a dynamic library. (unchecked functionality, not even sure when this would be used)
//
// For now FLX aims to be exception-free

#define FLX_VERSION_MAJOR	0
#define FLX_VERSION_MINOR	2
#define FLX_VERSION_PATCH	1
#define FLX_VERSION			"0.2.1"



// ===== compiler ===== //

#define IMP_FLX_COMPILER_UNKNOWN_	(-1)
#define IMP_FLX_COMPILER_MSVC_		0
#define IMP_FLX_COMPILER_GCC_		1
#define IMP_FLX_COMPILER_CLANG_		2

#if defined(_MSC_VER)
	#define IMP_FLX_COMPILER_ IMP_FLX_COMPILER_MSVC_
#elif defined(__GNUC__)
	#define IMP_FLX_COMPILER_ IMP_FLX_COMPILER_GCC_
#elif defined(__clang__)
	#define IMP_FLX_COMPILER_ IMP_FLX_COMPILER_CLANG_
#else
	#define IMP_FLX_COMPILER_ IMP_FLX_COMPILER_UNKNOWN_
	#error "Unknown compiler. Some code may break. You may remove this error at your own risk."
#endif // compiler



// ===== platform ===== //

#define IMP_FLX_PLATFORM_UNKNOWN_	(-1)
#define IMP_FLX_PLATFORM_WINDOWS_	0
#define IMP_FLX_PLATFORM_LINUX_		1
#define IMP_FLX_PLATFORM_APPLE_		2

#if defined(_WIN32)
	#define IMP_FLX_PLATFORM_ IMP_FLX_PLATFORM_WINDOWS_
#elif defined(__linux__)
	#define IMP_FLX_PLATFORM_ IMP_FLX_PLATFORM_LINUX_
#elif defined(__APPLE__)
	#define IMP_FLX_PLATFORM_ IMP_FLX_PLATFORM_APPLE_
#else
	#define IMP_FLX_PLATFORM_ IMP_FLX_PLATFORM_UNKNOWN_
	#error "Unknown platform. Some code may break. You may remove this error at your own risk."
#endif // platform



// ===== architecture  ===== //

#define IMP_FLX_ARCH_UNKNOWN_	(-1)
#define IMP_FLX_ARCH_X86_		0
#define IMP_FLX_ARCH_X64_		1

#if IMP_FLX_COMPILER_ == IMP_FLX_COMPILER_MSVC_
	#if defined(_M_IX86)
		#define IMP_FLX_ARCH_ IMP_FLX_ARCH_X86_
	#elif defined(_M_X64) || defined(_M_AMD64)
		#define IMP_FLX_ARCH_ IMP_FLX_ARCH_X64_
	#else
		#define IMP_FLX_ARCH_ IMP_FLX_ARCH_UNKNOWN_
		#error "Unknown architecture. Some code may break. You may remove this error at your own risk."
	#endif
#elif IMP_FLX_COMPILER_ == IMP_FLX_COMPILER_GCC_ || IMP_FLX_COMPILER_ == IMP_FLX_COMPILER_CLANG_
	#if defined(__i386__) || defined(__i386)
		#define IMP_FLX_ARCH_ IMP_FLX_ARCH_X86_
	#elif defined(__x86_64__)
		#define IMP_FLX_ARCH_ IMP_FLX_ARCH_X64_
	#else
		#define IMP_FLX_ARCH_ IMP_FLX_ARCH_UNKNOWN_
		#error "Unknown architecture. Some code may break. You may remove this error at your own risk."
	#endif
#else
	#define IMP_FLX_ARCH_ IMP_FLX_ARCH_UNKNOWN_
	#error "The architecture could not be determined because the compiler is unknown. Some code may break. You may remove this error at your own risk."
#endif // architecture



// ===== configuration ===== //

#define IMP_FLX_CONFIGURATION_UNKNOWN_	(-1)
#define IMP_FLX_CONFIGURATION_DEBUG_	0
#define IMP_FLX_CONFIGURATION_RELEASE_	1

#if defined(NDEBUG)
	#define IMP_FLX_CONFIGURATION_ IMP_FLX_CONFIGURATION_RELEASE_
	#define FLX_RELEASE
#else
	#define IMP_FLX_CONFIGURATION_ IMP_FLX_CONFIGURATION_DEBUG_
	#define FLX_DEBUG
#endif // configuration



// ===== C++ version ===== //

#if IMP_FLX_COMPILER_ == IMP_FLX_COMPILER_MSVC_ // MSVC uses '_MSVC_LANG' instead of '__cplusplus'
	#define IMP_FLX_LANG_ _MSVC_LANG
#else 
	#define IMP_FLX_LANG_ __cplusplus
#endif // IMP_FLX_LANG_

#if IMP_FLX_LANG_ >= 202002L
	#define IMP_FLX_HAS_CXX20_ 1
#else
	#define IMP_FLX_HAS_CXX20_ 0
	#error "Unsupported C++ Standard. FLX requires C++20 or higher."
#endif // IMP_FLX_HAS_CXX20_



// ===== common macros ===== //

#define FLX_		::flx::
#define FLX_BEGIN_	namespace flx {
#define FLX_END_	} // namespace flx

#define IMP_		::flx::imp::
#define IMP_BEGIN_	namespace imp {
#define IMP_END_	} // namespace imp

#if defined(FLX_BUILDING_SHARED) && defined(FLX_USING_SHARED)
	#error "Cannot define both FLX_BUILDING_SHARED and FLX_USING_SHARED."
#endif

#if defined(FLX_BUILDING_SHARED) // Building as a DLL/SO
	#if IMP_FLX_COMPILER_ == IMP_FLX_COMPILER_MSVC_
		#define FLX_API_ __declspec(dllexport)
	#else
		#define FLX_API_ __attribute__((visibility("default")))
	#endif
#elif defined(FLX_USING_SHARED) // Using as DLL/SO
	#if IMP_FLX_COMPILER_ == IMP_FLX_COMPILER_MSVC_
		#define FLX_API_ __declspec(dllimport)
	#else
		#define FLX_API_ __attribute__((visibility("default")))
	#endif
#else // Building as static lib
	#define FLX_API_
#endif // FLX_API_

#if IMP_FLX_ARCH_ == IMP_FLX_ARCH_X86_
	#define IMP_FLX_SIZE_TYPE_ unsigned int
#elif IMP_FLX_ARCH_ == IMP_FLX_ARCH_X64_
	#define IMP_FLX_SIZE_TYPE_ unsigned long long
#else // assuming other architectures are at least 32 bit
	#define IMP_FLX_SIZE_TYPE_ unsigned int
#endif // IMP_FLX_SIZE_TYPE_

#if IMP_FLX_COMPILER_ == IMP_FLX_COMPILER_MSVC_
	#define IMP_FLX_ASSUME_(expr) __assume(expr)
#elif IMP_FLX_COMPILER_ == IMP_FLX_COMPILER_GCC_ || IMP_FLX_COMPILER_ == IMP_FLX_COMPILER_GCC_
	#define IMP_FLX_ASSUME_(expr) __builtin_assume(expr)
#else
	#define IMP_FLX_ASSUME_(expr) 
#endif // IMP_FLX_ASSUME_

#define IMP_FLX_DEPRICATE_EXCEPTIONS_ [[deprecated("As of FLX v." FLX_VERSION ": throwable functions are depricated, use flx::nothrow tag.")]]



// ===== types ===== //

#ifdef FLX_ALL_MEMBERS_ARE_PUBLIC
	#define flx_public public
	#define flx_protected public
	#define flx_private public
#else
	#define flx_public public
	#define flx_protected protected
	#define flx_private private
#endif // FLX_ALL_MEMBERS_ARE_PUBLIC

FLX_BEGIN_

inline namespace types
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

	using szt	= IMP_FLX_SIZE_TYPE_;
} // namespace types

FLX_END_



// ===== assert ===== //

#if defined(FLX_DEBUG)
	#include <cassert>
	#define FLX_ASSERT_(expr) assert(expr)
#else
	#define FLX_ASSERT_(expr) ((void)0)
#endif // FLX_DEBUG


// ===== terminate ===== //

FLX_BEGIN_

FLX_API_ inline const c8* last_error = "NULL";
FLX_API_ inline void (*on_terminate) () noexcept =
[]() noexcept
	{
		// make program crash
		*(i32*)(nullptr) = 0;

		while (true)
		{
			*(i32*)(nullptr) = 0;
		}
	};

FLX_API_ inline void terminate(const c8* const error_msg = last_error) noexcept
{
	FLX_ASSERT_(false && *error_msg);

	FLX_ on_terminate();
};

FLX_END_



#endif // IMP_FLX_IMP_CORE_HPP_