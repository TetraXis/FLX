#ifndef FLX_TYPE_TRAITS_HPP
#define FLX_TYPE_TRAITS_HPP

namespace flx
{
	// ===== is_same ===== //

	template <typename a, typename b>
	constexpr bool is_same = false;

	template <typename a>
	constexpr bool is_same<a, a> = true;



	// ===== is_any_of ===== //

	template<typename ty, typename... types>
	constexpr bool is_any_of = (is_same<ty, types> || ...);



	// ===== is_array ===== //

	template <typename>
	constexpr bool is_array = false;

	template <typename ty>
	constexpr bool is_array<ty[]> = true;

	template <typename ty, unsigned long long size>
	constexpr bool is_array<ty[size]> = true;



	// ===== is_const ===== //

	template <typename>
	constexpr bool is_const = false;

	template <typename ty>
	constexpr bool is_const<const ty> = true;



	// ===== is_volatile ===== //

	template <typename>
	constexpr bool is_volatile = false;

	template <typename ty>
	constexpr bool is_volatile<volatile ty> = true;



	// ===== is_lvalue_reference ===== //

	template <typename>
	constexpr bool is_lvalue_reference = false;

	template <typename ty>
	constexpr bool is_lvalue_reference<ty&> = true;


	// ===== is_integral ===== //

	template <typename ty>
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

	template <typename ty>
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

	template <typename ty>
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

	template <typename ty>
	constexpr bool is_floating_point = is_any_of
	<
		ty,
		float,
		double,
		long double
	>;


	// ===== is_class ===== //

#if defined(__clang__) || defined(_MSC_VER)
	// Clang,  MSVC
	#define IMP_FLX_IS_CLASS(ty) __is_class(ty)
#elif defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__EDG__)
	// GCC, Intel ICC, EDG-based compilers
	#define IMP_FLX_IS_CLASS(ty) __is_class(ty)
#else
	// unknown compiler - raise error
	#error "flx_type_traits.hpp::is_class unkown compiler. Could not generate 'is_class' trait. Replace with your eqivalent of '__is_class' in the 'flx_type_traits.hpp' header."
	#define IMP_FLX_IS_CLASS(ty) false // your replacement here
#endif

	template <typename ty>
	constexpr bool is_class = IMP_FLX_IS_CLASS(ty);



	// ===== is_destructible ===== //

#if defined(__clang__) || defined(_MSC_VER)
	// Clang,  MSVC
	#define IMP_FLX_IS_DESTRUCTIBLE(ty) __is_destructible(ty)
#elif defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__EDG__)
	// GCC, Intel ICC, EDG-based compilers
	#define IMP_FLX_IS_DESTRUCTIBLE(ty) __has_destructor(ty)
#else
	// unknown compiler - raise error
	#error "flx_type_traits.hpp::is_destructible unkown compiler. Could not generate 'is_destructible' trait. Replace with your eqivalent of '__has_destructor' in the 'flx_type_traits.hpp' header."
	#define IMP_FLX_IS_DESTRUCTIBLE(ty) false // your replacement here
#endif

	template <typename ty>
	constexpr bool is_destructible = IMP_FLX_IS_DESTRUCTIBLE(ty);



	// ===== is_nothrow_constructible ===== //

	template <typename ty, typename... args>
	constexpr bool is_nothrow_constructible = __is_nothrow_constructible(ty, args...); // Cannot create a macro to accepts variadic arguments.



	// ===== is_nothrow_destructible ===== //

#if defined(__clang__) || defined(_MSC_VER)
	// Clang, MSVC
	#define IMP_FLX_IS_NOTHROW_DESTRUCTIBLE(ty) __is_nothrow_destructible(ty)
#elif defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__EDG__)
	// GCC, Intel ICC, EDG-based compilers
	#define IMP_FLX_IS_NOTHROW_DESTRUCTIBLE(ty) __has_nothrow_destructor(ty)
#else
	// unknown compiler - raise error
	#error "flx_type_traits.hpp::is_nothrow_destructible unknown compiler. Could not generate 'is_nothrow_destructible' trait. Replace with your equivalent of '__has_nothrow_destructor' in the 'flx_type_traits.hpp' header."
	#define IMP_FLX_IS_NOTHROW_DESTRUCTIBLE(ty) false // your replacement here
#endif

	template <typename ty>
	constexpr bool is_nothrow_destructible = IMP_FLX_IS_NOTHROW_DESTRUCTIBLE(ty);



	// ===== is_trivially_constructible ===== //

#if defined(__clang__) || defined(_MSC_VER)
	// Clang,  MSVC
	#define IMP_FLX_IS_TRIVIALLY_CONSTRUCTIBLE(ty) __is_trivially_constructible(ty)
#elif defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__EDG__)
	// GCC, Intel ICC, EDG-based compilers
	#define IMP_FLX_IS_TRIVIALLY_CONSTRUCTIBLE(ty) __has_trivial_constructor(ty)
#else
	// unknown compiler - raise error
	#error "flx_type_traits.hpp::is_trivially_constructible unkown compiler. Could not generate 'is_trivially_constructible' trait. Replace with your eqivalent of '__has_trivial_constructor' in the 'flx_type_traits.hpp' header."
	#define IMP_FLX_IS_TRIVIALLY_CONSTRUCTIBLE(ty) false // your replacement here
#endif

	template <typename ty>
	constexpr bool is_trivially_constructible = IMP_FLX_IS_TRIVIALLY_CONSTRUCTIBLE(ty);



	// ===== is_trivially_destructible ===== //

#if defined(__clang__) || defined(_MSC_VER)
	// Clang,  MSVC
	#define IMP_FLX_IS_TRIVIALLY_DESTRUCTIBLE(ty) __is_trivially_destructible(ty)
#elif defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__EDG__)
	// GCC, Intel ICC, EDG-based compilers
	#define IMP_FLX_IS_TRIVIALLY_DESTRUCTIBLE(ty) __has_trivial_destructor(ty)
#else
	// unknown compiler - raise error
	#error "flx_type_traits.hpp::is_trivially_destructible unkown compiler. Could not generate 'is_trivially_destructible' trait. Replace with your eqivalent of '__has_trivial_destructor' in the 'flx_type_traits.hpp' header."
	#define IMP_FLX_IS_TRIVIALLY_DESTRUCTIBLE(ty) false // your replacement here
#endif

	template <typename ty>
	constexpr bool is_trivially_destructible = IMP_FLX_IS_TRIVIALLY_DESTRUCTIBLE(ty);



	// ===== add_rvalue_reference ===== //

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

	template <typename ty>
	using add_rvalue_reference = typename imp_add_rvalue_reference<ty>::type;



	// ===== remove_reference ===== //

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

	template <typename ty>
	using remove_reference = typename imp_remove_reference<ty>::type;



	// ===== is_nothrow_copy_constructible ===== //

#if defined(__clang__) || defined(_MSC_VER)
	// Clang, MSVC
#define IMP_FLX_IS_NOTHROW_COPY_CONSTRUCTIBLE(ty) __is_nothrow_constructible(ty, add_lvalue_reference<ty) // TODO: here
#elif defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__EDG__)
	// GCC, Intel ICC, EDG-based compilers
#define IMP_FLX_IS_NOTHROW_COPY_CONSTRUCTIBLE(ty) __is_nothrow_constructible(ty, add_lvalue_reference<ty)
#else
	// unknown compiler - raise error
	#error "flx_type_traits.hpp::is_nothrow_copy_constructible unknown compiler. Could not generate 'is_nothrow_copy_constructible' trait. Replace with your equivalent of '__is_nothrow_constructible' in the 'flx_type_traits.hpp' header."
	#define IMP_FLX_IS_NOTHROW_COPY_CONSTRUCTIBLE(ty) false // your replacement here
#endif

	template <typename ty>
	constexpr bool is_nothrow_copy_constructible = IMP_FLX_IS_NOTHROW_COPY_CONSTRUCTIBLE(ty);



	// ===== declval ===== //

	template<typename ty>
	add_rvalue_reference<ty> declval() noexcept
	{
		static_assert(false, "Calling declval is ill-formed, see N4950 [declval]/2.");
	}



	// ===== move ====== //

	template<typename ty>
	constexpr remove_reference<ty>&& move(ty&& obj) noexcept
	{
		return static_cast<remove_reference<ty>&&>(obj);
	}



	// ===== forward ===== //

	template<typename ty>
	constexpr ty&& forward(remove_reference<ty>& val) noexcept
	{
		return static_cast<ty&&>(val);
	}

	template<typename ty>
	constexpr ty&& forward(remove_reference<ty>&& val) noexcept
	{
		static_assert(!is_lvalue_reference<ty>, "flx_type_traits.hpp::forward bad forward call.");
		return static_cast<ty&&>(val);
	}
} // namespace flx

#endif // !FLX_TYPE_TRAITS_HPP
