#ifndef FLX_CONCEPTS_HPP
#define FLX_CONCEPTS_HPP

#include "flx_types.hpp"
#include "flx_type_traits.hpp"

namespace flx
{
	// ===== same_as ===== //

	template <typename a, typename b>
	concept same_as = is_same<a, b> && is_same<b, a>;



	// ===== destructible ===== //

	template <typename ty>
	concept destructible = is_destructible<ty>;



	// ===== nothrow_destructible ===== //

	template <typename ty>
	concept nothrow_destructible = is_nothrow_destructible<ty>;



	// ===== constructible_from ===== //

	template <typename ty, typename... args>
	concept constructible_from = destructible<ty> && __is_constructible(ty, args...);



	// ===== convertible_to ===== //

	template <typename from, typename to>
	concept convertible_to = __is_convertible_to(from, to) && requires
	{
		static_cast<to>(flx::declval<from>());
	};



	// ===== move_constructible ===== //

	template <typename ty>
	concept move_constructible = constructible_from<ty, ty> && convertible_to<ty, ty>;


	
	// ===== copy_constructible ===== //

	template <typename ty>
	concept copy_constructible =
		move_constructible<ty> &&
		constructible_from<ty, ty&> && convertible_to<ty&, ty> &&
		constructible_from<ty, const ty> && convertible_to<const ty, ty> &&
		constructible_from<ty, const ty&> && convertible_to<const ty&, ty>;



	// ===== unsigned_integral ===== //

	template <typename ty>
	concept unsigned_integral = is_unsigned_integral<ty>;
} // namespace flx

#endif // !FLX_CONCEPTS_HPP