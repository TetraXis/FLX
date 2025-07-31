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
	constexpr const ty& (max) (const ty& a, const ty& b) noexcept
	{
		return a > b ? a : b;
	}
	
	template<typename ty>
	constexpr const ty& (min) (const ty& a, const ty& b) noexcept
	{
		return a < b ? a : b;
	}

	// converts x, y, width to index for buffer array
	template<typename ty>
	constexpr const ty (xy_to_idx) (ty x, ty y, ty width) noexcept
	{
		return x + y * width;
	}
} // namespace flx

#endif // !FLX_UTILITY_HPP