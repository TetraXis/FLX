#ifndef FLX_INC_CORE_OPT_HPP
#define FLX_INC_CORE_OPT_HPP

// This header defines options for building and using FLX.

// ===== FORCED COMPILER ===== //

#if defined(FLX_OPT_FORCE_COMPILER_GCC) + defined(FLX_OPT_FORCE_COMPILER_CLANG) + \
	defined(FLX_OPT_FORCE_COMPILER_MSVC) > 1
	#error "Only one compiler can be enforced."
#endif



// ===== FORCED ARCHITECTURE ===== //

#if defined(FLX_OPT_FORCE_ARCH_X86_32) + defined(FLX_OPT_FORCE_ARCH_X86_64) + \
	defined(FLX_OPT_FORCE_ARCH_ARM_32) + defined(FLX_OPT_FORCE_ARCH_ARM_64) > 1
	#error "Only one architecture can be enforced."
#endif



// ====== FORCED OS ===== //

#if defined(FLX_OPT_FORCE_OS_WINDOWS) + defined(FLX_OPT_FORCE_OS_LINUX) + \
	defined(FLX_OPT_FORCE_OS_APPLE) + defined(FLX_OPT_FORCE_OS_FREEBSD) + \
	defined(FLX_OPT_FORCE_OS_ANDROID) > 1
	#error "Only one OS can be enforced."
#endif



// ===== FORCED CRT ===== //

#if defined(FLX_OPT_FORCE_CRT_UCRT) + defined(FLX_OPT_FORCE_CRT_MSVCRT) + \
	defined(FLX_OPT_FORCE_CRT_GLIBC) + defined(FLX_OPT_FORCE_CRT_MUSL) + \
	defined(FLX_OPT_FORCE_CRT_APPLE) + defined(FLX_OPT_FORCE_CRT_FREEBSD) + \
	defined(FLX_OPT_FORCE_CRT_ANDROID) > 1
	#error "Only one CRT can be enforced."
#endif



#endif //FLX_INC_CORE_OPT_HPP