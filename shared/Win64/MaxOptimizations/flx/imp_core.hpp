#ifndef IMP_FLX_CORE_HPP_
#define IMP_FLX_CORE_HPP_

/// ====== Main header for internal macros ====== ///
// Defines:
// FLX_BUILDING_SHARED:	Define when building FLX as a dynamic library. (unchecked functionality)
// FLX_USING_SHARED:	Define when using FLX as a dynamic library. (unchecked functionality, not even sure when this would be used)



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
		#error "Uknown architecture. Some code may break. You may remove this error at your own risk."
	#endif
#else // assuming other compilers use same macros as GCC and clang
	#if defined(__i386__) || defined(__i386)
		#define IMP_FLX_ARCH_ IMP_FLX_ARCH_X86_
	#elif defined(__x86_64__)
		#define IMP_FLX_ARCH_ IMP_FLX_ARCH_X64_
	#else
		#define IMP_FLX_ARCH_ IMP_FLX_ARCH_UNKNOWN_
		#error "Uknown architecture. Some code may break. You may remove this error at your own risk."
	#endif
#endif // architecture



// ===== C++ version ===== //

#if IMP_FLX_COMPILER_ == IMP_FLX_COMPILER_MSVC_ // MSVC uses '_MSVC_LANG' instead of 'cplusplus'
	#define IMP_FLX_LANG_ _MSVC_LANG
#else 
	#define IMP_FLX_LANG_ __cplusplus
#endif // Macro for MSVC

#if IMP_FLX_LANG_ >= 202002L
	#define IMP_FLX_HAS_CXX20_ 1
#else
	#define IMP_FLX_HAS_CXX20_ 0
	#error "Unsupported C++ Standard. FLX requires C++20 or beyond."
#endif // C++ version



// ===== common macros ===== //

#define FLX_		::flx::
#define FLX_BEGIN_	namespace flx {
#define FLX_END_	} // namespace flx

#if defined(FLX_BUILDING_SHARED) // Building as a DLL/SO
	#if IMP_FLX_PLATFORM_ == IMP_FLX_PLATFORM_WINDOWS_
		#define FLX_API_ __declspec(dllexport)
	#else
		#define FLX_API_ __attribute__((visibility("default")))
	#endif
#elif defined(FLX_USING_SHARED) // Using as DLL/SO
	#if IMP_FLX_PLATFORM_ == IMP_FLX_PLATFORM_WINDOWS_
		#define FLX_API_ __declspec(dllimport)
	#else
		#define FLX_API_ __attribute__((visibility("default")))
	#endif
#else // Building as static lib
	#define FLX_API_
#endif // Macro for FLX_API_

#if IMP_FLX_ARCH_ == IMP_FLX_ARCH_X86_
#define IMP_FLX_SIZE_TYPE_ unsigned int
#else // assuming other architectures are atleast 64 bit
#define IMP_FLX_SIZE_TYPE_ unsigned long long
#endif // Macro for IMP_FLX_SIZE_TYPE_



#endif // IMP_FLX_CORE_HPP_