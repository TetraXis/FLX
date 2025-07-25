#ifndef FLX_UTILITY_HPP
#define FLX_UTILITY_HPP

#include "flx_types.hpp"

#ifndef NDEBUG
#include <cassert>
#else
#define assert(expr) ((void)0)
#endif // !NDEBUG

namespace flx
{
	template<typename ty>
	constexpr const ty& max(const ty& a, const ty& b) noexcept
	{
		return a > b ? a : b;
	}

	template<typename ty>
	constexpr const ty& min(const ty& a, const ty& b) noexcept
	{
		return a < b ? a : b;
	}
} // namespace flx

#endif // !FLX_UTILITY_HPP