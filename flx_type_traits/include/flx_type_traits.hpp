#ifndef FLX_TYPE_TRAITS_HPP
#define FLX_TYPE_TRAITS_HPP

namespace flx
{
	// ===== is_same ===== //

	template <typename a, typename b>
	constexpr bool is_same = false;

	template <typename a>
	constexpr bool is_same<a, a> = true; // was false, WHY?



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


	// ===== is_trivially_constructible ===== //

#if defined(__clang__) || defined(_MSC_VER)
	// Clang,  MSVC
	#define FLX_IS_TRIVIALLY_CONSTRUCTIBLE(ty) __is_trivially_constructible(ty)
#elif defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__EDG__)
	// GCC, Intel ICC, EDG-based compilers
	#define FLX_IS_TRIVIALLY_CONSTRUCTIBLE(ty) __has_trivial_constructor(ty)
#else
	// unknown compiler - fallback
	#warning "flx_type_traits.hpp::is_trivially_constructible unkown compiler. Could not generate 'is_trivially_constructible' trait. Replace with your eqivalent of '__has_trivial_constructor' in the 'flx_type_traits.hpp' header."
	#define FLX_IS_TRIVIALLY_CONSTRUCTIBLE(ty) false
#endif

	template <typename ty>
	constexpr bool is_trivially_constructible = FLX_IS_TRIVIALLY_CONSTRUCTIBLE(ty);



	// ===== is_trivially_destructible ===== //

#if defined(__clang__) || defined(_MSC_VER)
	// Clang,  MSVC
	#define FLX_IS_TRIVIALLY_DESTRUCTIBLE(ty) __is_trivially_destructible(ty)
#elif defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__EDG__)
	// GCC, Intel ICC, EDG-based compilers
	#define FLX_IS_TRIVIALLY_DESTRUCTIBLE(ty) __has_trivial_destructor(ty)
#else
	// unknown compiler - fallback
	#warning "flx_type_traits.hpp::is_trivially_destructible unkown compiler. Could not generate 'is_trivially_destructible' trait. Replace with your eqivalent of '__has_trivial_destructor' in the 'flx_type_traits.hpp' header."
	#define FLX_IS_TRIVIALLY_DESTRUCTIBLE(ty) false
#endif

	template <typename ty>
	constexpr bool is_trivially_destructible = FLX_IS_TRIVIALLY_DESTRUCTIBLE(ty);



	// ===== is_class ===== //

#if defined(__clang__) || defined(_MSC_VER)
	// Clang,  MSVC
	#define FLX_IS_CLASS(ty) __is_class(ty)
#elif defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__EDG__)
	// GCC, Intel ICC, EDG-based compilers
	#define FLX_IS_CLASS(ty) __is_class(ty)
#else
	// unknown compiler - raise error
	#error "flx_type_traits.hpp::is_class unkown compiler. Could not generate 'is_class' trait. Replace with your eqivalent of '__is_class' in the 'flx_type_traits.hpp' header."
	#define FLX_IS_CLASS(ty) false // you replacement here
#endif

	template <typename ty>
	constexpr bool is_class = FLX_IS_CLASS(ty);



	// ===== remove_reference ===== //

	template <typename ty>
	struct remove_reference_struct
	{
		using type = ty;
	};

	template <typename ty>
	struct remove_reference_struct<ty&>
	{
		using type = ty;
	};

	template <typename ty>
	struct remove_reference_struct<ty&&>
	{
		using type = ty;
	};

	template <typename ty>
	using remove_reference = typename remove_reference_struct<ty>::type;



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
		// TODO: add "Cannot forward rvalue as lvalue"
		return static_cast<ty&&>(val);
	}
} // namespace flx

#endif // !FLX_TYPE_TRAITS_HPP
