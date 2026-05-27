#ifndef FLX_INC_CORE_CRT_ISO_C_LIMITS_HPP
#define FLX_INC_CORE_CRT_ISO_C_LIMITS_HPP

// This is a part of a compatibility layer between FLX and CRT.
// It is needed since Windows' CRT does not follow POSIX.

// To Dev: when linking to new CRT functions, do not forget to add both variants.

#include "flx/core.hpp"

namespace flx::crt
{
	// flx::types are not used because they define presice bit amount (see long on different platforms)

	#if defined(__CHAR_BIT__)
		constexpr u64 CHAR_BIT = __CHAR_BIT__;
	#else
		constexpr u64 CHAR_BIT = 8;
	#endif

	constexpr u64 BOOL_MAX = 1;
	constexpr u64 UCHAR_MAX  = (unsigned char)~0;
	constexpr u64 USHRT_MAX  = (unsigned short)~0;
	constexpr u64 UINT_MAX   = ~0U;
	constexpr u64 ULONG_MAX  = ~0UL;
	constexpr u64 ULLONG_MAX = ~0ULL;

	constexpr u64 SCHAR_MAX  = (signed char)(UCHAR_MAX >> 1);
	constexpr u64 SHRT_MAX   = (short)(USHRT_MAX >> 1);
	constexpr u64 INT_MAX    = (int)(UINT_MAX >> 1);
	constexpr u64 LONG_MAX   = (long)(ULONG_MAX >> 1);
	constexpr u64 LLONG_MAX  = (long long)(ULLONG_MAX >> 1);

	constexpr u64 SCHAR_MIN  = -SCHAR_MAX - 1;
	constexpr u64 SHRT_MIN   = -SHRT_MAX - 1;
	constexpr u64 INT_MIN    = -INT_MAX - 1;
	constexpr u64 LONG_MIN   = -LONG_MAX - 1;
	constexpr u64 LLONG_MIN  = -LLONG_MAX - 1;

	#if defined(__CHAR_UNSIGNED__) || defined(_CHAR_UNSIGNED)
		constexpr u64 CHAR_MIN = 0;
		constexpr u64 CHAR_MAX = UCHAR_MAX;
	#else
		constexpr u64 CHAR_MIN = SCHAR_MIN;
		constexpr u64 CHAR_MAX = SCHAR_MAX;
	#endif

	constexpr u64 BOOL_WIDTH   = 1;
	constexpr u64 CHAR_WIDTH   = CHAR_BIT;
	constexpr u64 SCHAR_WIDTH  = sizeof(signed char) * CHAR_BIT;
	constexpr u64 SHRT_WIDTH   = sizeof(short) * CHAR_BIT;
	constexpr u64 INT_WIDTH    = sizeof(int) * CHAR_BIT;
	constexpr u64 LONG_WIDTH   = sizeof(long) * CHAR_BIT;
	constexpr u64 LLONG_WIDTH  = sizeof(long long) * CHAR_BIT;
	constexpr u64 UCHAR_WIDTH  = sizeof(unsigned char) * CHAR_BIT;
	constexpr u64 USHRT_WIDTH  = sizeof(unsigned short) * CHAR_BIT;
	constexpr u64 UINT_WIDTH   = sizeof(unsigned int) * CHAR_BIT;
	constexpr u64 ULONG_WIDTH  = sizeof(unsigned long) * CHAR_BIT;
	constexpr u64 ULLONG_WIDTH = sizeof(unsigned long long) * CHAR_BIT;

	#if FLX_ENV_OS == FLX_ENV_OS_WINDOWS
		constexpr u64 MB_LEN_MAX = 5;
	#else
		constexpr u64 MB_LEN_MAX = 16;
	#endif

	#if defined(__BITINT_MAXWIDTH__)
		constexpr u64 BITINT_MAXWIDTH = __BITINT_MAXWIDTH__;
	#else
		#if FLX_ENV_COMPILER == FLX_ENV_COMPILER_MSVC
			constexpr u64 BITINT_MAXWIDTH = ULLONG_WIDTH;
		#else
			constexpr u64 BITINT_MAXWIDTH = 128;
		#endif
	#endif
} // namespace flx::crt

#endif //FLX_INC_CORE_CRT_ISO_C_LIMITS_HPP
