#ifndef IMP_UTILITY_HPP_
#define IMP_UTILITY_HPP_

#include "flx/imp_core.hpp"

FLX_BEGIN_

FLX_API_ template<typename ty>
constexpr const ty& (max)(const ty& a, const ty& b) noexcept
{
	return a > b ? a : b;
}

FLX_API_ template<typename ty>
constexpr const ty& (min)(const ty& a, const ty& b) noexcept
{
	return a < b ? a : b;
}

// converts x, y, width to index for 2D array
FLX_API_ template<typename ty>
constexpr const ty& (xy_to_idx)(const ty& x, const ty& y, const ty& width) noexcept
{
	return x + y * width;
}

FLX_END_

#endif // IMP_UTILITY_HPP_