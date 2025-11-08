#ifndef IMP_TYPE_TRAITS_HPP_
#define IMP_TYPE_TRAITS_HPP_

#include "flx/imp_core.hpp"

FLX_BEGIN_

// ===== is_same ===== //

FLX_API_ template <typename a, typename b>
constexpr bool is_same = false;

template <typename a>
constexpr bool is_same<a, a> = true;



// ===== is_any_of ===== //

FLX_API_ template<typename ty, typename... types>
constexpr bool is_any_of = (is_same<ty, types> || ...);



// ===== is_array ===== //

FLX_API_ template <typename>
constexpr bool is_array = false;

template <typename ty>
constexpr bool is_array<ty[]> = true;

template <typename ty, unsigned long long size>
constexpr bool is_array<ty[size]> = true;



// ===== is_const ===== //

FLX_API_ template <typename>
constexpr bool is_const = false;

template <typename ty>
constexpr bool is_const<const ty> = true;



// ===== is_volatile ===== //

FLX_API_ template <typename>
constexpr bool is_volatile = false;

template <typename ty>
constexpr bool is_volatile<volatile ty> = true;



// ===== is_pointer ===== //

IMP_BEGIN_

template <typename>
constexpr bool imp_is_pointer = false;

template <typename ty>
constexpr bool imp_is_pointer<ty*> = true;

template <typename ty>
constexpr bool imp_is_pointer<ty* const> = true;

template <typename ty>
constexpr bool imp_is_pointer<ty* volatile> = true;

template <typename ty>
constexpr bool imp_is_pointer<ty* const volatile> = true;

IMP_END_

FLX_API_ template <typename ty>
constexpr bool is_pointer = IMP_ imp_is_pointer<ty>;



// ===== is_reference ===== //

FLX_API_ template <typename>
constexpr bool is_reference = false;

template <typename ty>
constexpr bool is_reference<ty&> = true;

template <typename ty>
constexpr bool is_reference<ty&&> = true;



// ===== is_lvalue_reference ===== //

FLX_API_ template <typename>
constexpr bool is_lvalue_reference = false;

template <typename ty>
constexpr bool is_lvalue_reference<ty&> = true;



// ===== is_function ===== //

FLX_API_ template <typename ty>
constexpr bool is_function = !FLX_ is_const<const ty> && !FLX_ is_reference<ty>;


// ===== is_integral ===== //

FLX_API_ template <typename ty>
constexpr bool is_integral = is_any_of
<
	ty,
	signed char,
	unsigned char,
	signed short,
	unsigned short,
	signed int,
	unsigned int,
	signed long,
	unsigned long,
	signed long long,
	unsigned long long
>;


// ===== is_signed_integral ===== //

FLX_API_ template <typename ty>
constexpr bool is_signed_integral = is_any_of
<
	ty,
	signed char,
	signed short,
	signed int,
	signed long,
	signed long long
>;


// ===== is_unsigned_integral ===== //

FLX_API_ template <typename ty>
constexpr bool is_unsigned_integral = is_any_of
<
	ty,
	unsigned char,
	unsigned short,
	unsigned int,
	unsigned long,
	unsigned long long
>;


// ===== is_floating_point ===== //

FLX_API_ template <typename ty>
constexpr bool is_floating_point = is_any_of
<
	ty,
	float,
	double,
	long double
>;


// ===== is_class ===== //

#if IMP_COMPILER_ == IMP_COMPILER_MSVC_ || IMP_COMPILER_ == IMP_COMPILER_GCC_ || IMP_COMPILER_ == IMP_COMPILER_CLANG_
	FLX_API_ template <typename ty>
	constexpr bool is_class = __is_class(ty);
#else
	FLX_API_ template <typename ty>
	constexpr bool is_class = false;
	#error "flx/type_traits.hpp::is_class: unkown compiler. Could not generate 'is_class' trait. Replace with your eqivalent of '__is_class' in the 'flx/type_traits.hpp' header."
#endif // is_class_



// ===== is_destructible ===== //

#if IMP_COMPILER_ == IMP_COMPILER_MSVC_ || IMP_COMPILER_ == IMP_COMPILER_CLANG_
	FLX_API_ template <typename ty>
	constexpr bool is_destructible = __is_destructible(ty);
#elif IMP_COMPILER_ == IMP_COMPILER_GCC_
	FLX_API_ template <typename ty>
	constexpr bool is_destructible = __has_destructor(ty);
#else
	FLX_API_ template <typename ty>
	constexpr bool is_destructible = false;
	#error "flx/type_traits.hpp::is_destructible unkown compiler. Could not generate 'is_destructible' trait. Replace with your eqivalent of '__has_destructor' in the 'flx/type_traits.hpp' header."
#endif // is_destructible_



// ===== is_nothrow_constructible ===== //

#if IMP_COMPILER_ == IMP_COMPILER_MSVC_ || IMP_COMPILER_ == IMP_COMPILER_GCC_ || IMP_COMPILER_ == IMP_COMPILER_CLANG_
	FLX_API_ template <typename ty, typename... args>
	constexpr bool is_nothrow_constructible = __is_nothrow_constructible(ty, args...);
#else
	FLX_API_ template <typename ty, typename... args>
	constexpr bool is_nothrow_constructible = false;
	#error "flx/type_traits.hpp::is_nothrow_constructible: unkown compiler. Could not generate 'is_nothrow_constructible' trait. Replace with your eqivalent of '__is_nothrow_constructible' in the 'flx/type_traits.hpp' header."
#endif // is_nothrow_constructible_



// ===== is_nothrow_destructible ===== //

#if IMP_COMPILER_ == IMP_COMPILER_MSVC_ || IMP_COMPILER_ == IMP_COMPILER_CLANG_
	FLX_API_ template <typename ty>
	constexpr bool is_nothrow_destructible = __is_nothrow_destructible(ty);
#elif IMP_COMPILER_ == IMP_COMPILER_GCC_
	FLX_API_ template <typename ty>
	constexpr bool is_nothrow_destructible = __has_nothrow_destructor(ty);
#else
	FLX_API_ template <typename ty>
	constexpr bool is_nothrow_destructible = false;
	#error "flx/type_traits.hpp::is_nothrow_destructible unknown compiler. Could not generate 'is_nothrow_destructible' trait. Replace with your equivalent of '__has_nothrow_destructor' in the 'flx/type_traits.hpp' header."
#endif // is_nothrow_destructible_



// ===== is_nothrow_move_constructible ===== //

#if IMP_COMPILER_ == IMP_COMPILER_MSVC_ || IMP_COMPILER_ == IMP_COMPILER_GCC_ || IMP_COMPILER_ == IMP_COMPILER_CLANG_
	FLX_API_ template <typename ty>
		constexpr bool is_nothrow_move_constructible = __is_nothrow_constructible(ty, ty);
#else
	FLX_API_ template <typename ty>
		constexpr bool is_nothrow_constructible = false;
#error "flx/type_traits.hpp::is_nothrow_move_constructible: unkown compiler. Could not generate 'is_nothrow_move_constructible' trait. Replace with your eqivalent of '__is_nothrow_constructible' in the 'flx/type_traits.hpp' header."
#endif // is_nothrow_constructible_



// ===== is_trivially_constructible ===== //

#if IMP_COMPILER_ == IMP_COMPILER_MSVC_ || IMP_COMPILER_ == IMP_COMPILER_CLANG_
	FLX_API_ template <typename ty>
	constexpr bool is_trivially_constructible = __is_trivially_constructible(ty);
#elif IMP_COMPILER_ == IMP_COMPILER_GCC_
	FLX_API_ template <typename ty>
	constexpr bool is_trivially_constructible = __has_trivial_constructor(ty);
#else
	FLX_API_ template <typename ty>
	constexpr bool is_trivially_constructible = false;
	#error "flx/type_traits.hpp::is_trivially_constructible unkown compiler. Could not generate 'is_trivially_constructible' trait. Replace with your eqivalent of '__has_trivial_constructor' in the 'flx/type_traits.hpp' header."
#endif // is_trivially_constructible_



// ===== is_trivially_destructible ===== //

#if IMP_COMPILER_ == IMP_COMPILER_MSVC_ || IMP_COMPILER_ == IMP_COMPILER_CLANG_
	FLX_API_ template <typename ty>
	constexpr bool is_trivially_destructible = __is_trivially_destructible(ty);
#elif IMP_COMPILER_ == IMP_COMPILER_GCC_
	FLX_API_ template <typename ty>
	constexpr bool is_trivially_destructible = __has_trivial_destructor(ty);
#else
	FLX_API_ template <typename ty>
	constexpr bool is_trivially_destructible = false;
	#error "flx/type_traits.hpp::is_trivially_destructible unkown compiler. Could not generate 'is_trivially_destructible' trait. Replace with your eqivalent of '__has_trivial_destructor' in the 'flx/type_traits.hpp' header."
#endif // is_trivially_destructible_



// ===== add_rvalue_reference ===== //

IMP_BEGIN_

template <typename ty>
struct imp_add_rvalue_reference
{
	using type = ty&&;
};

template <typename ty>
struct imp_add_rvalue_reference<ty&>
{
	using type = ty&;
};

template <typename ty>
struct imp_add_rvalue_reference<ty&&>
{
	using type = ty&&;
};

IMP_END_

FLX_API_ template <typename ty>
using add_rvalue_reference = typename IMP_ imp_add_rvalue_reference<ty>::type;



// ===== add_lvalue_reference ===== //


IMP_BEGIN_

template <typename ty>
struct imp_add_lvalue_reference
{
	using type = ty&;
};

template <>
struct imp_add_lvalue_reference<void>
{
	using type = void;
};

template <>
struct imp_add_lvalue_reference<const void>
{
	using type = const void;
};

template <>
struct imp_add_lvalue_reference<volatile void>
{
	using type = volatile void;
};

template <>
struct imp_add_lvalue_reference<const volatile void>
{
	using type = const volatile void;
};

IMP_END_

FLX_API_ template <typename ty>
using add_lvalue_reference = typename IMP_ imp_add_lvalue_reference<ty>::type;



// ===== remove_reference ===== //

IMP_BEGIN_

template <typename ty>
struct imp_remove_reference
{
	using type = ty;
};

template <typename ty>
struct imp_remove_reference<ty&>
{
	using type = ty;
};

template <typename ty>
struct imp_remove_reference<ty&&>
{
	using type = ty;
};

IMP_END_

FLX_API_ template <typename ty>
using remove_reference = typename IMP_ imp_remove_reference<ty>::type;


// ===== is_nothrow_copy_constructible ===== //

#if IMP_COMPILER_ == IMP_COMPILER_MSVC_ || IMP_COMPILER_ == IMP_COMPILER_GCC_ || IMP_COMPILER_ == IMP_COMPILER_CLANG_
	FLX_API_ template <typename ty>
	constexpr bool is_nothrow_copy_constructible = __is_nothrow_constructible(ty, add_lvalue_reference<ty>);
#else
	FLX_API_ template <typename ty>
	constexpr bool is_nothrow_copy_constructible = false;
#error "flx/type_traits.hpp::is_nothrow_copy_constructible unknown compiler. Could not generate 'is_nothrow_copy_constructible' trait. Replace with your equivalent of '__is_nothrow_constructible' in the 'flx/type_traits.hpp' header."
#endif // is_nothrow_copy_constructible_



FLX_API_ [[nodiscard]] constexpr bool is_constant_evaluated() noexcept
{
	return __builtin_is_constant_evaluated();
}



// ===== declval ===== //

FLX_API_ template<typename ty>
add_rvalue_reference<ty> declval() noexcept
{
	static_assert(false, "Calling declval is ill-formed, see N4950 [declval]/2.");
}



// ===== move ===== //

FLX_API_ template<typename ty>
constexpr remove_reference<ty>&& move(ty&& obj) noexcept
{
	return static_cast<remove_reference<ty>&&>(obj);
}



// ===== forward ===== //

FLX_API_ template<typename ty>
constexpr ty&& forward(remove_reference<ty>& val) noexcept
{
	return static_cast<ty&&>(val);
}

FLX_API_ template<typename ty>
constexpr ty&& forward(remove_reference<ty>&& val) noexcept
{
	static_assert(!is_lvalue_reference<ty>, "flx/type_traits.hpp::forward bad forward call.");
	return static_cast<ty&&>(val);
}

FLX_END_

#endif // IMP_TYPE_TRAITS_HPP_