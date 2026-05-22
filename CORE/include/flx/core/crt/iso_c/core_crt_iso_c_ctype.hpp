#ifndef FLX_INC_CORE_CRT_ISO_C_CTYPE_HPP
#define FLX_INC_CORE_CRT_ISO_C_CTYPE_HPP

// This is a part of a compatibility layer between FLX and CRT.
// It is needed since Windows' CRT does not follow POSIX.

// To Dev: when linking to new CRT functions, do not forget to add both variants.

#include "flx/core.hpp"

extern "C"
{
	using namespace flx::types;

	i32	isalnum		(i32 c);
	i32	isalpha		(i32 c);
	i32	isblank		(i32 c);
	i32	iscntrl		(i32 c);
	i32	isdigit		(i32 c);
	i32	isgraph		(i32 c);
	i32	islower		(i32 c);
	i32	isprint		(i32 c);
	i32	ispunct		(i32 c);
	i32	isspace		(i32 c);
	i32	isupper		(i32 c);
	i32	isxdigit	(i32 c);
	i32	tolower		(i32 c);
	i32	toupper		(i32 c);
} // extern "C"

namespace flx::crt
{
	inline i32	isalnum(i32 c)	noexcept { return ::isalnum		(c); }
	inline i32	isalpha(i32 c)	noexcept { return ::isalpha		(c); }
	inline i32	isblank(i32 c)	noexcept { return ::isblank		(c); }
	inline i32	iscntrl(i32 c)	noexcept { return ::iscntrl		(c); }
	inline i32	isdigit(i32 c)	noexcept { return ::isdigit		(c); }
	inline i32	isgraph(i32 c)	noexcept { return ::isgraph		(c); }
	inline i32	islower(i32 c)	noexcept { return ::islower		(c); }
	inline i32	isprint(i32 c)	noexcept { return ::isprint		(c); }
	inline i32	ispunct(i32 c)	noexcept { return ::ispunct		(c); }
	inline i32	isspace(i32 c)	noexcept { return ::isspace		(c); }
	inline i32	isupper(i32 c)	noexcept { return ::isupper		(c); }
    inline i32	isxdigit(i32 c)	noexcept { return ::isxdigit	(c); }
	inline i32	tolower(i32 c)	noexcept { return ::tolower		(c); }
	inline i32	toupper(i32 c)	noexcept { return ::toupper		(c); }
} // namespace flx::crt

#endif //FLX_INC_CORE_CRT_ISO_C_CTYPE_HPP
