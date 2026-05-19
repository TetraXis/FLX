module;

// This module defines type traits.
// Note: naming does not match std naming, there are no _v or _t.

#include "flx/core.hpp"

export module flx.type_traits;

export namespace flx
{
	// ===== is_same ===== //

	template <typename ty_a, typename ty_b>
	constexpr bool is_same = false;

	template <typename ty>
	constexpr bool is_same<ty, ty> = true;



	// ===== remove_cv ===== //

	namespace imp
	{
		template <typename ty>
		struct remove_cv_imp
		{
			using type = ty;
		};

		template <typename ty>
		struct remove_cv_imp<const ty>
		{
			using type = ty;
		};

		template <typename ty>
		struct remove_cv_imp<volatile ty>
		{
			using type = ty;
		};

		template <typename ty>
		struct remove_cv_imp<const volatile ty>
		{
			using type = ty;
		};
	} // namespace imp

	template<typename ty>
	using remove_cv = typename ::flx::imp::remove_cv_imp<ty>::type;



	// ===== remove_reference ===== //

	namespace imp
	{
		template<typename ty>
		struct remove_reference_imp
		{
			using type = ty;
		};

		template<typename ty>
		struct remove_reference_imp<ty&>
		{
			using type = ty;
		};

		template<typename ty>
		struct remove_reference_imp<ty&&>
		{
			using type = ty;
		};
	} // namespace imp

	template<typename ty>
	using remove_reference = typename ::flx::imp::remove_reference_imp<ty>::type;



	// ===== add_rvalue_reference ===== //

	namespace imp
	{
		template<typename ty>
		struct add_rvalue_reference_imp
		{
			using type = ty&&;
		};

		template<typename ty>
		requires ::flx::is_same<::flx::remove_cv<ty>, void>
		struct add_rvalue_reference_imp<ty>
		{
			using type = ty;
		};
	} // namespace imp

	template<typename ty>
	using add_rvalue_reference = typename ::flx::imp::add_rvalue_reference_imp<ty>::type;



	// ===== declval ===== //

	template <typename ty>
	::flx::add_rvalue_reference<ty> declval() noexcept 
	{
		static_assert(false, "Calling declval is ill-formed.");
	}



	// ===== forward ===== //

	template <class ty>
	[[nodiscard]] constexpr ty&& forward(::flx::remove_reference<ty>& arg) noexcept 
	{
		return static_cast<ty&&>(arg);
	}

	template <class ty>
	[[nodiscard]] constexpr ty&& forward(::flx::remove_reference<ty>&& arg) noexcept 
	{
		return static_cast<ty&&>(arg);
	}



	// ===== move ===== //

	template <class ty>
	constexpr ::flx::remove_reference<ty>&& move(ty&& arg) noexcept 
	{
		return static_cast<::flx::remove_reference<ty>&&>(arg);
	}

} // namespace flx