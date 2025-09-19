#ifndef IMP_FLX_CONCEPTS_HPP_
#define IMP_FLX_CONCEPTS_HPP_

#include "flx/imp_core.hpp"
#include "flx/type_traits.hpp"

FLX_BEGIN_

// ===== same_as ===== //

FLX_API_ template <typename a, typename b>
concept same_as = is_same<a, b>&& is_same<b, a>;



// ===== destructible ===== //

FLX_API_ template <typename ty>
concept destructible = __is_nothrow_destructible(ty);
// C++20 Standard requires 'destructible concept' to check for 'nothrow destructible'. See [concept.destructible].



// ===== constructible_from ===== //

FLX_API_ template <typename ty, typename... args>
concept constructible_from = destructible<ty> && __is_constructible(ty, args...);



// ===== convertible_to ===== //

FLX_API_ template <typename from, typename to>
concept convertible_to = __is_convertible_to(from, to) && requires
{
	static_cast<to>(flx::declval<from>());
};



// ===== move_constructible ===== //

FLX_API_ template <typename ty>
concept move_constructible = constructible_from<ty, ty>&& convertible_to<ty, ty>;



// ===== copy_constructible ===== //

FLX_API_ template <typename ty>
concept copy_constructible =
move_constructible<ty> &&
constructible_from<ty, ty&>&& convertible_to<ty&, ty>&&
constructible_from<ty, const ty>&& convertible_to<const ty, ty>&&
constructible_from<ty, const ty&>&& convertible_to<const ty&, ty>;



// ===== nothrow_copy_constructible ===== //



// ===== unsigned_integral ===== //

FLX_API_ template <typename ty>
concept unsigned_integral = is_unsigned_integral<ty>;

FLX_END_

#endif // IMP_FLX_CONCEPTS_HPP_