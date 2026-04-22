#pragma once

#include "test/core.hpp"

#include "flx/type_traits.hpp"
#include <type_traits>

namespace test
{
	inline void type_traits()
	{
		group = "type_traits.hpp";

		// ===== is_same ===== //
		{
			subgroup = "is_same";

			enum E { dummy };
			check(flx::is_same<int, int> == std::is_same_v<int, int>, "Mismatch with STD 00");
			check(flx::is_same<int, float> == std::is_same_v<int, float>, "Mismatch with STD 01");
			check(flx::is_same<float, float> == std::is_same_v<float, float>, "Mismatch with STD 02");
			check(flx::is_same<const int, const int> == std::is_same_v<const int, const int>, "Mismatch with STD 03");
			check(flx::is_same<const int, int> == std::is_same_v<const int, int>, "Mismatch with STD 04");
			check(flx::is_same<int, const int> == std::is_same_v<int, const int>, "Mismatch with STD 05");
			check(flx::is_same<volatile int, int> == std::is_same_v<volatile int, int>, "Mismatch with STD 06");
			check(flx::is_same<volatile int, volatile int> == std::is_same_v<volatile int, volatile int>, "Mismatch with STD 07");
			check(flx::is_same<std::string, int> == std::is_same_v<std::string, int>, "Mismatch with STD 08");
			check(flx::is_same<std::string, std::string> == std::is_same_v<std::string, std::string>, "Mismatch with STD 09");check(flx::is_same<const volatile int, const volatile int> == std::is_same_v<const volatile int, const volatile int>, "Mismatch with STD 0A");
			check(flx::is_same<const volatile int, const int> == std::is_same_v<const volatile int, const int>, "Mismatch with STD 0B");
			check(flx::is_same<const volatile int, volatile int> == std::is_same_v<const volatile int, volatile int>, "Mismatch with STD 0C");
			check(flx::is_same<int&, int&> == std::is_same_v<int&, int&>, "Mismatch with STD 0D");
			check(flx::is_same<int&, int> == std::is_same_v<int&, int>, "Mismatch with STD 0E");
			check(flx::is_same<int&&, int&&> == std::is_same_v<int&&, int&&>, "Mismatch with STD 0F");
			check(flx::is_same<int&&, int&> == std::is_same_v<int&&, int&>, "Mismatch with STD 10");
			check(flx::is_same<int*, int*> == std::is_same_v<int*, int*>, "Mismatch with STD 11");
			check(flx::is_same<int*, const int*> == std::is_same_v<int*, const int*>, "Mismatch with STD 12");
			check(flx::is_same<int[5], int[5]> == std::is_same_v<int[5], int[5]>, "Mismatch with STD 13");
			check(flx::is_same<int[5], int[6]> == std::is_same_v<int[5], int[6]>, "Mismatch with STD 14");
			check(flx::is_same<void, void> == std::is_same_v<void, void>, "Mismatch with STD 15");
			check(flx::is_same<void, int> == std::is_same_v<void, int>, "Mismatch with STD 16");
			check(flx::is_same<std::nullptr_t, std::nullptr_t> == std::is_same_v<std::nullptr_t, std::nullptr_t>, "Mismatch with STD 17");
			check(flx::is_same<enum E, enum E> == std::is_same_v<enum E, enum E>, "Mismatch with STD 18");
			check(flx::is_same<int(), int()> == std::is_same_v<int(), int()>, "Mismatch with STD 19");
			check(flx::is_same<int(), int(int)> == std::is_same_v<int(), int(int)>, "Mismatch with STD 1A");

			subgroup = "NULL";
		}



		// ===== remove_cv ===== //
		{
			subgroup = "remove_cv";

			enum E { dummy };
			check(flx::is_same<flx::remove_cv<int>, std::remove_cv_t<int>>, "Mismatch with STD 00");
			check(flx::is_same<flx::remove_cv<const int>, std::remove_cv_t<const int>>, "Mismatch with STD 01");
			check(flx::is_same<flx::remove_cv<volatile int>, std::remove_cv_t<volatile int>>, "Mismatch with STD 02");
			check(flx::is_same<flx::remove_cv<const volatile int>, std::remove_cv_t<const volatile int>>, "Mismatch with STD 03");
			check(flx::is_same<flx::remove_cv<int*>, std::remove_cv_t<int*>>, "Mismatch with STD 04");
			check(flx::is_same<flx::remove_cv<const int*>, std::remove_cv_t<const int*>>, "Mismatch with STD 05");
			check(flx::is_same<flx::remove_cv<volatile int*>, std::remove_cv_t<volatile int*>>, "Mismatch with STD 06");
			check(flx::is_same<flx::remove_cv<const volatile int*>, std::remove_cv_t<const volatile int*>>, "Mismatch with STD 07");
			check(flx::is_same<flx::remove_cv<int* const>, std::remove_cv_t<int* const>>, "Mismatch with STD 08");
			check(flx::is_same<flx::remove_cv<int* volatile>, std::remove_cv_t<int* volatile>>, "Mismatch with STD 09");
			check(flx::is_same<flx::remove_cv<int* const volatile>, std::remove_cv_t<int* const volatile>>, "Mismatch with STD 0A");
			check(flx::is_same<flx::remove_cv<const int* const>, std::remove_cv_t<const int* const>>, "Mismatch with STD 0B");
			check(flx::is_same<flx::remove_cv<const int[5]>, std::remove_cv_t<const int[5]>>, "Mismatch with STD 0C");
			check(flx::is_same<flx::remove_cv<volatile int[5]>, std::remove_cv_t<volatile int[5]>>, "Mismatch with STD 0D");
			check(flx::is_same<flx::remove_cv<const volatile int[5]>, std::remove_cv_t<const volatile int[5]>>, "Mismatch with STD 0E");
			check(flx::is_same<flx::remove_cv<void>, std::remove_cv_t<void>>, "Mismatch with STD 0F");
			check(flx::is_same<flx::remove_cv<const void>, std::remove_cv_t<const void>>, "Mismatch with STD 10");
			check(flx::is_same<flx::remove_cv<int&>, std::remove_cv_t<int&>>, "Mismatch with STD 11");
			check(flx::is_same<flx::remove_cv<const int&>, std::remove_cv_t<const int&>>, "Mismatch with STD 12");
			check(flx::is_same<flx::remove_cv<int&&>, std::remove_cv_t<int&&>>, "Mismatch with STD 13");
			check(flx::is_same<flx::remove_cv<enum E>, std::remove_cv_t<enum E>>, "Mismatch with STD 14");

			subgroup = "NULL";
		}



	}
} // namespace test