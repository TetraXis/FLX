#ifndef FLX_CONCEPTS_HPP
#define FLX_CONCEPTS_HPP

#include "flx_types.hpp"
#include "flx_type_traits.hpp"

namespace flx
{
	// ===== same_as ===== //

	template <typename a, typename b>
	concept same_as = is_same<a, b> && is_same<b, a>;



	// ===== copy_constructible ===== //

	template <typename ty>
	concept copy_constructible = requires(const ty& val)
	{
		ty{ val };
		{ [](const ty& test) { return test; }(val) } -> same_as<ty>;
	};
} // namespace flx

#endif // !FLX_CONCEPTS_HPP