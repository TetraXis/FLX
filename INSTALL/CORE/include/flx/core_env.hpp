#ifndef FLX_INC_CORE_ENV_HPP
#define FLX_INC_CORE_ENV_HPP

// This header detects environment in which FLX is being built.

#include "flx/core_opt.hpp"

// ===== COMPILER ===== //

#define FLX_ENV_COMPILER_UNKNOWN	0
#define FLX_ENV_COMPILER_GCC		1
#define FLX_ENV_COMPILER_CLANG		2
#define FLX_ENV_COMPILER_MSVC		3

#if defined(FLX_OPT_FORCE_COMPILER_GCC)
	#define FLX_ENV_COMPILER FLX_ENV_COMPILER_GCC
#elif defined(FLX_OPT_FORCE_COMPILER_CLANG)
	#define FLX_ENV_COMPILER FLX_ENV_COMPILER_CLANG
#elif defined(FLX_OPT_FORCE_COMPILER_MSVC)
	#define FLX_ENV_COMPILER FLX_ENV_COMPILER_MSVC
#else
	#if defined(__clang__) // should be before GNUC
		#define FLX_ENV_COMPILER FLX_ENV_COMPILER_CLANG
	#elif defined(__GNUC__)
		#define FLX_ENV_COMPILER FLX_ENV_COMPILER_GCC
	#elif defined(_MSC_VER)
		#define FLX_ENV_COMPILER FLX_ENV_COMPILER_MSVC
	#else
		#define FLX_ENV_COMPILER FLX_ENV_COMPILER_UNKNOWN
	#endif
#endif


#if !defined(FLX_ENV_COMPILER) || FLX_ENV_COMPILER == FLX_ENV_COMPILER_UNKNOWN
	#error "Could not resolve compiler."
#endif

#if FLX_ENV_COMPILER != FLX_ENV_COMPILER_GCC
	#error "Unsupported compiler."
#endif



// ===== C++ VERSION ===== //

#if FLX_ENV_COMPILER == FLX_ENV_COMPILER_MSVC
	#define FLX_ENV_CXX_LANG _MSVC_LANG
#else
	#define FLX_ENV_CXX_LANG __cplusplus
#endif



// ===== ARCHITECTURE ===== //

#define FLX_ENV_ARCH_UNKNOWN	0
#define FLX_ENV_ARCH_X86_32		1
#define FLX_ENV_ARCH_X86_64		2
#define FLX_ENV_ARCH_ARM_32		3
#define FLX_ENV_ARCH_ARM_64		4

#if defined(FLX_OPT_FORCE_ARCH_X86_32)
	#define FLX_ENV_ARCH FLX_ENV_ARCH_X86_32
#elif defined(FLX_OPT_FORCE_ARCH_X86_64)
	#define FLX_ENV_ARCH FLX_ENV_ARCH_X86_64
#elif defined(FLX_OPT_FORCE_ARCH_ARM_32)
	#define FLX_ENV_ARCH FLX_ENV_ARCH_ARM_32
#elif defined(FLX_OPT_FORCE_ARCH_ARM_64)
	#define FLX_ENV_ARCH FLX_ENV_ARCH_ARM_64
#else
	#if defined(__i386__) || defined(_M_IX86)
		#define FLX_ENV_ARCH FLX_ENV_ARCH_X86_32
	#elif defined(__x86_64__) || defined(_M_X64)
		#define FLX_ENV_ARCH FLX_ENV_ARCH_X86_64
	#elif defined(__arm__) || defined(_M_ARM)
		#define FLX_ENV_ARCH FLX_ENV_ARCH_ARM_32
	#elif defined(__aarch64__) || defined(_M_ARM64)
		#define FLX_ENV_ARCH FLX_ENV_ARCH_ARM_64
	#else
		#define FLX_ENV_ARCH FLX_ENV_ARCH_UNKNOWN
	#endif
#endif



#if !defined(FLX_ENV_ARCH) || FLX_ENV_ARCH == FLX_ENV_ARCH_UNKNOWN
	#error "Could not resolve architecture."
#endif



// ===== OS ===== //

#define FLX_ENV_OS_UNKNOWN	0
#define FLX_ENV_OS_WINDOWS	1
#define FLX_ENV_OS_LINUX	2
#define FLX_ENV_OS_APPLE	3
#define FLX_ENV_OS_FREEBSD	4
#define FLX_ENV_OS_ANDROID	5

#if defined(FLX_OPT_FORCE_OS_WINDOWS)
	#define FLX_ENV_OS FLX_ENV_OS_WINDOWS
#elif defined(FLX_OPT_FORCE_OS_ANDROID)
	#define FLX_ENV_OS FLX_ENV_OS_ANDROID
#elif defined(FLX_OPT_FORCE_OS_LINUX)
	#define FLX_ENV_OS FLX_ENV_OS_LINUX
#elif defined(FLX_OPT_FORCE_OS_APPLE)
	#define FLX_ENV_OS FLX_ENV_OS_APPLE
#elif defined(FLX_OPT_FORCE_OS_FREEBSD)
	#define FLX_ENV_OS FLX_ENV_OS_FREEBSD
#else
	#if defined(_WIN32)
		#define FLX_ENV_OS FLX_ENV_OS_WINDOWS
	#elif defined(__ANDROID__) // should be before LINUX
		#define FLX_ENV_OS FLX_ENV_OS_ANDROID
	#elif defined(__linux__)
		#define FLX_ENV_OS FLX_ENV_OS_LINUX
	#elif defined(__APPLE__)
		#define FLX_ENV_OS FLX_ENV_OS_APPLE
	#elif defined(__FreeBSD__)
		#define FLX_ENV_OS FLX_ENV_OS_FREEBSD
	#else
		#define FLX_ENV_OS FLX_ENV_OS_UNKNOWN
	#endif
#endif



#if !defined(FLX_ENV_OS) || FLX_ENV_OS == FLX_ENV_OS_UNKNOWN
	#error "Could not resolve operating system."
#endif



// ===== CRT ===== //

#define FLX_ENV_CRT_UNKNOWN	0
#define FLX_ENV_CRT_UCRT	1
#define FLX_ENV_CRT_MSVCRT	2
#define FLX_ENV_CRT_GLIBC	3
#define FLX_ENV_CRT_MUSL	4
#define FLX_ENV_CRT_APPLE	5
#define FLX_ENV_CRT_FREEBSD	6
#define FLX_ENV_CRT_ANDROID	7

#if defined(FLX_OPT_FORCE_CRT_UCRT)
	#define FLX_ENV_CRT FLX_ENV_CRT_UCRT
#elif defined(FLX_OPT_FORCE_CRT_MSVCRT)
	#define FLX_ENV_CRT FLX_ENV_CRT_MSVCRT
#elif defined(FLX_OPT_FORCE_CRT_GLIBC)
	#define FLX_ENV_CRT FLX_ENV_CRT_GLIBC
#elif defined(FLX_OPT_FORCE_CRT_MUSL)
	#define FLX_ENV_CRT FLX_ENV_CRT_MUSL
#elif defined(FLX_OPT_FORCE_CRT_APPLE)
	#define FLX_ENV_CRT FLX_ENV_CRT_APPLE
#elif defined(FLX_OPT_FORCE_CRT_FREEBSD)
	#define FLX_ENV_CRT FLX_ENV_CRT_FREEBSD
#elif defined(FLX_OPT_FORCE_CRT_ANDROID)
	#define FLX_ENV_CRT FLX_ENV_CRT_ANDROID
#else
	#if defined(__UCRT__)
		#define FLX_ENV_CRT FLX_ENV_CRT_UCRT
	#elif defined(__MSVCRT__)
		#define FLX_ENV_CRT FLX_ENV_CRT_MSVCRT
	#elif defined(__GLIBC__)
		#define FLX_ENV_CRT FLX_ENV_CRT_GLIBC
	#elif defined(__MUSL__)
		#define FLX_ENV_CRT FLX_ENV_CRT_MUSL
	#elif defined(__APPLE__)
		#define FLX_ENV_CRT FLX_ENV_CRT_APPLE
	#elif defined(__FreeBSD__)
		#define FLX_ENV_CRT FLX_ENV_CRT_FREEBSD
	#elif defined(__ANDROID__) || defined(__BIONIC__)
		#define FLX_ENV_CRT FLX_ENV_CRT_ANDROID
	#else
		#define FLX_ENV_CRT FLX_ENV_CRT_UNKNOWN
	#endif
#endif

#if  !defined(FLX_ENV_CRT) || FLX_ENV_CRT == FLX_ENV_CRT_UNKNOWN
	#error "Could not resolve C Runtime."
#endif



#endif //FLX_INC_CORE_ENV_HPP