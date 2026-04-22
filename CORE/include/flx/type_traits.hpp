#ifndef FLX_INC_TYPE_TRAITS_HPP
#define FLX_INC_TYPE_TRAITS_HPP

// This header defines type traits.
// Note: naming does not match std naming, there are no _v or _t.

namespace flx
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
	using remove_cv = ::flx::imp::remove_cv_imp<ty>::type;

} // namespace flx



#endif //FLX_INC_TYPE_TRAITS_HPP