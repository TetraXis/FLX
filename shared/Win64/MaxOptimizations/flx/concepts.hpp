#ifndef IMP_FLX_CONCEPTS_HPP_
#define IMP_FLX_CONCEPTS_HPP_

#include "flx/imp_core.hpp"
#include "flx/type_traits.hpp"

FLX_BEGIN_

// ===== same_as ===== //

FLX_API_ template <typename a, typename b>
concept same_as = FLX_ is_same<a, b> && FLX_ is_same<b, a>;



// ===== destructible ===== //

// C++20 Standard requires 'destructible concept' to check for 'nothrow destructible'. See [concept.destructible].
FLX_API_ template <typename ty>
concept destructible = __is_nothrow_destructible(ty);



// ===== constructible_from ===== //

FLX_API_ template <typename ty, typename... args>
concept constructible_from = FLX_ destructible<ty> && __is_constructible(ty, args...);



// ===== convertible_to ===== //

FLX_API_ template <typename from, typename to>
concept convertible_to = __is_convertible_to(from, to) && requires
{
	static_cast<to>(FLX_ declval<from>());
};



// ===== move_constructible ===== //

FLX_API_ template <typename ty>
concept move_constructible = FLX_ constructible_from<ty, ty> && FLX_ convertible_to<ty, ty>;



// ===== copy_constructible ===== //

FLX_API_ template <typename ty>
concept copy_constructible =
FLX_ move_constructible<ty> &&
FLX_ constructible_from<ty, ty&> && 
FLX_ convertible_to<ty&, ty> &&
FLX_ constructible_from<ty, const ty> && 
FLX_ convertible_to<const ty, ty> &&
FLX_ constructible_from<ty, const ty&> && 
FLX_ convertible_to<const ty&, ty>;



// ===== nothrow_copy_constructible ===== //



// ===== unsigned_integral ===== //

FLX_API_ template <typename ty>
concept unsigned_integral = FLX_ is_unsigned_integral<ty>;



// ===== allocatable ===== //

// see [allocator.requirements]
FLX_API_ template<typename ty>
concept allocatable =
!FLX_ is_const<ty> &&
!FLX_ is_function<ty> &&
!FLX_ is_reference<ty>;



// ===== allocator ===== //

FLX_API_ template <typename ty>
concept allocator = requires (ty alloc, szt size, typename ty::value_type* ptr)
{
	typename ty::value_type;
	requires FLX_ allocatable<typename ty::value_type>;
	{ alloc.allocate(size) } -> FLX_ same_as<typename ty::value_type*>;
	{ alloc.deallocate(ptr, size) } -> FLX_ same_as<void>; 

	//requires // to check if one is present
	//	requires {{ alloc.deallocate(ptr) } -> FLX_ same_as<void>; } ||
	//	requires {{ alloc.deallocate(ptr, size) } -> FLX_ same_as<void>; };
};



// ===== can_form_pointer ===== //

FLX_API_ template<typename ty>
concept can_form_pointer = FLX_ is_pointer<ty*>;

FLX_END_

#endif // IMP_FLX_CONCEPTS_HPP_