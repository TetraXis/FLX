#ifndef IMP_FLX_UTILITY_HPP_
#define IMP_FLX_UTILITY_HPP_

#include "flx/imp_core.hpp"
#include "flx/new.hpp"
#include "flx/type_traits.hpp"
#include "flx/concepts.hpp"

FLX_BEGIN_

FLX_API_ inline const c8* last_error;
FLX_API_ inline void (*on_terminate) () noexcept =
[]() noexcept
	{
		// make program crash
		*(int*)(nullptr) = 0;

		while (true)
		{
			*(int*)(nullptr) = 0;
		}
	};

FLX_API_ inline void terminate(const c8* const error_msg = last_error) noexcept 
{
	FLX_ASSERT_(false && *error_msg);

	FLX_ on_terminate();
};

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
constexpr const ty (xy_to_idx)(ty x, ty y, ty width) noexcept
{
	return x + y * width;
}



FLX_END_

#endif // IMP_FLX_UTILITY_HPP_