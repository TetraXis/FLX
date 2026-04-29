module;

//#include "test/core.hpp"
#include <type_traits>
#include <string>

//#include "flx/type_traits.hpp"
export module test.type_traits;

import test.core;
import flx.type_traits;

export namespace test
{
	inline void type_traits()
	{
		group = "type_traits.hpp";

		enum E { dummy };

		// ===== is_same ===== //
		{
			subgroup = "is_same";

			// fundamental types
			check(flx::is_same<int, int>									== std::is_same_v<int, int>,									"Mismatch with STD 00");
			check(flx::is_same<int, float>									== std::is_same_v<int, float>,									"Mismatch with STD 01");
			check(flx::is_same<float, float>								== std::is_same_v<float, float>,								"Mismatch with STD 02");
			check(flx::is_same<const int, const int>						== std::is_same_v<const int, const int>,						"Mismatch with STD 03");
			check(flx::is_same<const int, int>								== std::is_same_v<const int, int>,								"Mismatch with STD 04");
			check(flx::is_same<int, const int>								== std::is_same_v<int, const int>,								"Mismatch with STD 05");
			check(flx::is_same<volatile int, int>							== std::is_same_v<volatile int, int>,							"Mismatch with STD 06");
			check(flx::is_same<volatile int, volatile int>					== std::is_same_v<volatile int, volatile int>,					"Mismatch with STD 07");
			check(flx::is_same<const volatile int, const volatile int>		== std::is_same_v<const volatile int, const volatile int>,		"Mismatch with STD 08");
			check(flx::is_same<const volatile int, const int>				== std::is_same_v<const volatile int, const int>,				"Mismatch with STD 09");
			check(flx::is_same<const volatile int, volatile int>			== std::is_same_v<const volatile int, volatile int>,			"Mismatch with STD 0A");
			
			// references
			check(flx::is_same<int&, int&>									== std::is_same_v<int&, int&>,									"Mismatch with STD 0B");
			check(flx::is_same<int&, int>									== std::is_same_v<int&, int>,									"Mismatch with STD 0C");
			check(flx::is_same<int&&, int&&>								== std::is_same_v<int&&, int&&>,								"Mismatch with STD 0D");
			check(flx::is_same<int&&, int&>									== std::is_same_v<int&&, int&>,									"Mismatch with STD 0E");
			check(flx::is_same<const int&, const int&>						== std::is_same_v<const int&, const int&>,						"Mismatch with STD 0F");
			check(flx::is_same<volatile int&, volatile int&>				== std::is_same_v<volatile int&, volatile int&>,				"Mismatch with STD 10");
			check(flx::is_same<const volatile int&, const volatile int&>	== std::is_same_v<const volatile int&, const volatile int&>,	"Mismatch with STD 11");
			
			// pointers
			check(flx::is_same<int*, int*>									== std::is_same_v<int*, int*>,									"Mismatch with STD 12");
			check(flx::is_same<int*, const int*>							== std::is_same_v<int*, const int*>,							"Mismatch with STD 13");
			check(flx::is_same<const int*, const int*>						== std::is_same_v<const int*, const int*>,						"Mismatch with STD 14");
			check(flx::is_same<int* const, int* const>						== std::is_same_v<int* const, int* const>,						"Mismatch with STD 15");
			check(flx::is_same<int* volatile, int* volatile>				== std::is_same_v<int* volatile, int* volatile>,				"Mismatch with STD 16");
			check(flx::is_same<int* const volatile, int* const volatile>	== std::is_same_v<int* const volatile, int* const volatile>,	"Mismatch with STD 17");
			
			// arrays
			check(flx::is_same<int[5], int[5]>								== std::is_same_v<int[5], int[5]>,								"Mismatch with STD 18");
			check(flx::is_same<int[5], int[6]>								== std::is_same_v<int[5], int[6]>,								"Mismatch with STD 19");
			check(flx::is_same<const int[5], const int[5]>					== std::is_same_v<const int[5], const int[5]>,					"Mismatch with STD 1A");
			
			// function types
			check(flx::is_same<int(), int()>								== std::is_same_v<int(), int()>,								"Mismatch with STD 1B");
			check(flx::is_same<int(), int(int)>								== std::is_same_v<int(), int(int)>,								"Mismatch with STD 1C");
			check(flx::is_same<int(&)(), int(&)()>							== std::is_same_v<int(&)(), int(&)()>,							"Mismatch with STD 1D");
			check(flx::is_same<int(*)(int), int(*)(int)>					== std::is_same_v<int(*)(int), int(*)(int)>,					"Mismatch with STD 1E");
			
			// void
			check(flx::is_same<void, void>									== std::is_same_v<void, void>,									"Mismatch with STD 1F");
			check(flx::is_same<void, int>									== std::is_same_v<void, int>,									"Mismatch with STD 20");
			check(flx::is_same<const void, const void>						== std::is_same_v<const void, const void>,						"Mismatch with STD 21");
			check(flx::is_same<volatile void, volatile void>				== std::is_same_v<volatile void, volatile void>,				"Mismatch with STD 22");
			check(flx::is_same<const volatile void, const volatile void>	== std::is_same_v<const volatile void, const volatile void>,	"Mismatch with STD 23");
			
			// nullptr_t
			check(flx::is_same<std::nullptr_t, std::nullptr_t>				== std::is_same_v<std::nullptr_t, std::nullptr_t>,				"Mismatch with STD 24");
			
			// enum
			check(flx::is_same<enum E, enum E>								== std::is_same_v<enum E, enum E>,								"Mismatch with STD 25");
			check(flx::is_same<const enum E, const enum E>					== std::is_same_v<const enum E, const enum E>,					"Mismatch with STD 26");
			check(flx::is_same<volatile enum E, volatile enum E>			== std::is_same_v<volatile enum E, volatile enum E>,			"Mismatch with STD 27");
			
			// misc
			check(flx::is_same<std::string, int>							== std::is_same_v<std::string, int>,							"Mismatch with STD 28");
			check(flx::is_same<std::string, std::string>					== std::is_same_v<std::string, std::string>,					"Mismatch with STD 29");
			
			subgroup = "NULL";
		}



		// ===== remove_cv ===== //
		{
			subgroup = "remove_cv";
		
			// fundamental types
			check(std::is_same_v<	flx::remove_cv<int>,							std::remove_cv_t<int>							>, "Mismatch with STD 00");
			check(std::is_same_v<	flx::remove_cv<const int>,						std::remove_cv_t<const int>						>, "Mismatch with STD 01");
			check(std::is_same_v<	flx::remove_cv<volatile int>,					std::remove_cv_t<volatile int>					>, "Mismatch with STD 02");
			check(std::is_same_v<	flx::remove_cv<const volatile int>,				std::remove_cv_t<const volatile int>			>, "Mismatch with STD 03");
		
			// pointers
			check(std::is_same_v<	flx::remove_cv<int*>,							std::remove_cv_t<int*>							>, "Mismatch with STD 04");
			check(std::is_same_v<	flx::remove_cv<const int*>,						std::remove_cv_t<const int*>					>, "Mismatch with STD 05");
			check(std::is_same_v<	flx::remove_cv<volatile int*>,					std::remove_cv_t<volatile int*>					>, "Mismatch with STD 06");
			check(std::is_same_v<	flx::remove_cv<const volatile int*>,			std::remove_cv_t<const volatile int*>			>, "Mismatch with STD 07");
			check(std::is_same_v<	flx::remove_cv<int* const>,						std::remove_cv_t<int* const>					>, "Mismatch with STD 08");
			check(std::is_same_v<	flx::remove_cv<int* volatile>,					std::remove_cv_t<int* volatile>					>, "Mismatch with STD 09");
			check(std::is_same_v<	flx::remove_cv<int* const volatile>,			std::remove_cv_t<int* const volatile>			>, "Mismatch with STD 0A");
			check(std::is_same_v<	flx::remove_cv<const int* const>,				std::remove_cv_t<const int* const>				>, "Mismatch with STD 0B");
			check(std::is_same_v<	flx::remove_cv<const int* volatile>,			std::remove_cv_t<const int* volatile>			>, "Mismatch with STD 0C");
			check(std::is_same_v<	flx::remove_cv<const int* const volatile>,		std::remove_cv_t<const int* const volatile>		>, "Mismatch with STD 0D");
			check(std::is_same_v<	flx::remove_cv<volatile int* const>,			std::remove_cv_t<volatile int* const>			>, "Mismatch with STD 0E");
			check(std::is_same_v<	flx::remove_cv<volatile int* volatile>,			std::remove_cv_t<volatile int* volatile>		>, "Mismatch with STD 0F");
			check(std::is_same_v<	flx::remove_cv<volatile int* const volatile>,	std::remove_cv_t<volatile int* const volatile>	>, "Mismatch with STD 10");
		
			// arrays
			check(std::is_same_v<	flx::remove_cv<const int[5]>,					std::remove_cv_t<const int[5]>					>, "Mismatch with STD 11");
			check(std::is_same_v<	flx::remove_cv<volatile int[5]>,				std::remove_cv_t<volatile int[5]>				>, "Mismatch with STD 12");
			check(std::is_same_v<	flx::remove_cv<const volatile int[5]>,			std::remove_cv_t<const volatile int[5]>			>, "Mismatch with STD 13");
		
			// function types
			check(std::is_same_v<	flx::remove_cv<int()>,							std::remove_cv_t<int()>							>, "Mismatch with STD 14");
			check(std::is_same_v<	flx::remove_cv<const int()>,					std::remove_cv_t<const int()>					>, "Mismatch with STD 15");
			// volatile on return types are depricated as of C++20
		 // check(std::is_same_v<	flx::remove_cv<volatile int()>,					std::remove_cv_t<volatile int()>				>, "Mismatch with STD 16");
		 // check(std::is_same_v<	flx::remove_cv<const volatile int()>,			std::remove_cv_t<const volatile int()>			>, "Mismatch with STD 17");
		
			// void
			check(std::is_same_v<	flx::remove_cv<void>,							std::remove_cv_t<void>							>, "Mismatch with STD 18");
			check(std::is_same_v<	flx::remove_cv<const void>,						std::remove_cv_t<const void>					>, "Mismatch with STD 19");
			check(std::is_same_v<	flx::remove_cv<volatile void>,					std::remove_cv_t<volatile void>					>, "Mismatch with STD 1A");
			check(std::is_same_v<	flx::remove_cv<const volatile void>,			std::remove_cv_t<const volatile void>			>, "Mismatch with STD 1B");
		
			// references
			check(std::is_same_v<	flx::remove_cv<int&>,							std::remove_cv_t<int&>							>, "Mismatch with STD 1C");
			check(std::is_same_v<	flx::remove_cv<const int&>,						std::remove_cv_t<const int&>					>, "Mismatch with STD 1D");
			check(std::is_same_v<	flx::remove_cv<volatile int&>,					std::remove_cv_t<volatile int&>					>, "Mismatch with STD 1E");
			check(std::is_same_v<	flx::remove_cv<const volatile int&>,			std::remove_cv_t<const volatile int&>			>, "Mismatch with STD 1F");
			check(std::is_same_v<	flx::remove_cv<int&&>,							std::remove_cv_t<int&&>							>, "Mismatch with STD 20");
			check(std::is_same_v<	flx::remove_cv<const int&&>,					std::remove_cv_t<const int&&>					>, "Mismatch with STD 21");
			check(std::is_same_v<	flx::remove_cv<volatile int&&>,					std::remove_cv_t<volatile int&&>				>, "Mismatch with STD 22");
			check(std::is_same_v<	flx::remove_cv<const volatile int&&>,			std::remove_cv_t<const volatile int&&>			>, "Mismatch with STD 23");
		
			// enum
			check(std::is_same_v<	flx::remove_cv<enum E>,							std::remove_cv_t<enum E>						>, "Mismatch with STD 24");
			check(std::is_same_v<	flx::remove_cv<const enum E>,					std::remove_cv_t<const enum E>					>, "Mismatch with STD 25");
			check(std::is_same_v<	flx::remove_cv<volatile enum E>,				std::remove_cv_t<volatile enum E>				>, "Mismatch with STD 26");
			check(std::is_same_v<	flx::remove_cv<const volatile enum E>,			std::remove_cv_t<const volatile enum E>			>, "Mismatch with STD 27");
		
			subgroup = "NULL";
		}



		// ===== remove_reference ===== //
		{
			subgroup = "remove_reference";
		
			// fundamental types
			check(std::is_same_v<	flx::remove_reference<int>,						std::remove_reference_t<int>					>, "Mismatch with STD 00");
			check(std::is_same_v<	flx::remove_reference<const int>,				std::remove_reference_t<const int>				>, "Mismatch with STD 01");
			check(std::is_same_v<	flx::remove_reference<volatile int>,			std::remove_reference_t<volatile int>			>, "Mismatch with STD 02");
			check(std::is_same_v<	flx::remove_reference<const volatile int>,		std::remove_reference_t<const volatile int>		>, "Mismatch with STD 03");
		
			//lvalue references
			check(std::is_same_v<	flx::remove_reference<int&>,					std::remove_reference_t<int&>					>, "Mismatch with STD 04");
			check(std::is_same_v<	flx::remove_reference<const int&>,				std::remove_reference_t<const int&>				>, "Mismatch with STD 05");
			check(std::is_same_v<	flx::remove_reference<volatile int&>,			std::remove_reference_t<volatile int&>			>, "Mismatch with STD 06");
			check(std::is_same_v<	flx::remove_reference<const volatile int&>,		std::remove_reference_t<const volatile int&>	>, "Mismatch with STD 07");
		
			// rRvalue references
			check(std::is_same_v<	flx::remove_reference<int&&>,					std::remove_reference_t<int&&>					>, "Mismatch with STD 08");
			check(std::is_same_v<	flx::remove_reference<const int&&>,				std::remove_reference_t<const int&&>			>, "Mismatch with STD 09");
			check(std::is_same_v<	flx::remove_reference<volatile int&&>,			std::remove_reference_t<volatile int&&>			>, "Mismatch with STD 0A");
			check(std::is_same_v<	flx::remove_reference<const volatile int&&>,	std::remove_reference_t<const volatile int&&>	>, "Mismatch with STD 0B");
		
			// pointers
			check(std::is_same_v<	flx::remove_reference<int*>,					std::remove_reference_t<int*>					>, "Mismatch with STD 0C");
			check(std::is_same_v<	flx::remove_reference<const int*>,				std::remove_reference_t<const int*>				>, "Mismatch with STD 0D");
			check(std::is_same_v<	flx::remove_reference<int* const>,				std::remove_reference_t<int* const>				>, "Mismatch with STD 0E");
			check(std::is_same_v<	flx::remove_reference<int* volatile>,			std::remove_reference_t<int* volatile>			>, "Mismatch with STD 0F");
			check(std::is_same_v<	flx::remove_reference<int* const volatile>,		std::remove_reference_t<int* const volatile>	>, "Mismatch with STD 10");
			check(std::is_same_v<	flx::remove_reference<void*>,					std::remove_reference_t<void*>					>, "Mismatch with STD 11");
			check(std::is_same_v<	flx::remove_reference<const void*>,				std::remove_reference_t<const void*>			>, "Mismatch with STD 12");
		
			// pointer references
			check(std::is_same_v<	flx::remove_reference<int*&>,					std::remove_reference_t<int*&>					>, "Mismatch with STD 13");
			check(std::is_same_v<	flx::remove_reference<int*&&>,					std::remove_reference_t<int*&&>					>, "Mismatch with STD 14");
			check(std::is_same_v<	flx::remove_reference<const int*&>,				std::remove_reference_t<const int*&>			>, "Mismatch with STD 15");
			check(std::is_same_v<	flx::remove_reference<int* const&>,				std::remove_reference_t<int* const&>			>, "Mismatch with STD 16");
		
			// arrays
			check(std::is_same_v<	flx::remove_reference<int[5]>,					std::remove_reference_t<int[5]>					>, "Mismatch with STD 17");
			check(std::is_same_v<	flx::remove_reference<const int[5]>,			std::remove_reference_t<const int[5]>			>, "Mismatch with STD 18");
			check(std::is_same_v<	flx::remove_reference<int(&)[5]>,				std::remove_reference_t<int(&)[5]>				>, "Mismatch with STD 19");
			check(std::is_same_v<	flx::remove_reference<int(&&)[5]>,				std::remove_reference_t<int(&&)[5]>				>, "Mismatch with STD 1A");
		
			// function types
			check(std::is_same_v<	flx::remove_reference<int()>,					std::remove_reference_t<int()>					>, "Mismatch with STD 1B");
			check(std::is_same_v<	flx::remove_reference<int(&)()>,				std::remove_reference_t<int(&)()>				>, "Mismatch with STD 1C");
			check(std::is_same_v<	flx::remove_reference<int(&&)()>,				std::remove_reference_t<int(&&)()>				>, "Mismatch with STD 1D");
			check(std::is_same_v<	flx::remove_reference<int(*)(int)>,				std::remove_reference_t<int(*)(int)>			>, "Mismatch with STD 1E");
			check(std::is_same_v<	flx::remove_reference<int(&)(int)>,				std::remove_reference_t<int(&)(int)>			>, "Mismatch with STD 1F");
			check(std::is_same_v<	flx::remove_reference<int(&&)(int)>,			std::remove_reference_t<int(&&)(int)>			>, "Mismatch with STD 20");
		
			// void
			check(std::is_same_v<	flx::remove_reference<void>,					std::remove_reference_t<void>					>, "Mismatch with STD 21");
			check(std::is_same_v<	flx::remove_reference<const void>,				std::remove_reference_t<const void>				>, "Mismatch with STD 22");
			check(std::is_same_v<	flx::remove_reference<volatile void>,			std::remove_reference_t<volatile void>			>, "Mismatch with STD 23");
			check(std::is_same_v<	flx::remove_reference<const volatile void>,		std::remove_reference_t<const volatile void>	>, "Mismatch with STD 24");
		
			// enum
			check(std::is_same_v<	flx::remove_reference<enum E>,					std::remove_reference_t<enum E>					>, "Mismatch with STD 25");
			check(std::is_same_v<	flx::remove_reference<enum E&>,					std::remove_reference_t<enum E&>				>, "Mismatch with STD 26");
			check(std::is_same_v<	flx::remove_reference<enum E&&>,				std::remove_reference_t<enum E&&>				>, "Mismatch with STD 27");
		
			subgroup = "NULL";
		}



		// ===== add_rvalue_reference ===== //
		{
			subgroup = "add_rvalue_reference";

			// fundamental types
			check(std::is_same_v<	flx::add_rvalue_reference<int>,					std::add_rvalue_reference_t<int>					>, "Mismatch with STD 00");
			check(std::is_same_v<	flx::add_rvalue_reference<const int>,			std::add_rvalue_reference_t<const int>				>, "Mismatch with STD 01");
			check(std::is_same_v<	flx::add_rvalue_reference<volatile int>,		std::add_rvalue_reference_t<volatile int>			>, "Mismatch with STD 02");
			check(std::is_same_v<	flx::add_rvalue_reference<const volatile int>,	std::add_rvalue_reference_t<const volatile int>		>, "Mismatch with STD 03");

			// reference types
			check(std::is_same_v<	flx::add_rvalue_reference<int&>,				std::add_rvalue_reference_t<int&>					>, "Mismatch with STD 04");
			check(std::is_same_v<	flx::add_rvalue_reference<int&&>,				std::add_rvalue_reference_t<int&&>					>, "Mismatch with STD 05");
			check(std::is_same_v<	flx::add_rvalue_reference<const int&>,			std::add_rvalue_reference_t<const int&>				>, "Mismatch with STD 06");
			check(std::is_same_v<	flx::add_rvalue_reference<volatile int&>,		std::add_rvalue_reference_t<volatile int&>			>, "Mismatch with STD 07");
			check(std::is_same_v<	flx::add_rvalue_reference<const volatile int&>,	std::add_rvalue_reference_t<const volatile int&>	>, "Mismatch with STD 08");

			// pointers
			check(std::is_same_v<	flx::add_rvalue_reference<int*>,				std::add_rvalue_reference_t<int*>					>, "Mismatch with STD 09");
			check(std::is_same_v<	flx::add_rvalue_reference<int*&>,				std::add_rvalue_reference_t<int*&>					>, "Mismatch with STD 0A");
			check(std::is_same_v<	flx::add_rvalue_reference<int*&&>,				std::add_rvalue_reference_t<int*&&>					>, "Mismatch with STD 0B");
			check(std::is_same_v<	flx::add_rvalue_reference<const int*>,			std::add_rvalue_reference_t<const int*>				>, "Mismatch with STD 0C");
			check(std::is_same_v<	flx::add_rvalue_reference<int* const>,			std::add_rvalue_reference_t<int* const>				>, "Mismatch with STD 0D");
			check(std::is_same_v<	flx::add_rvalue_reference<int* volatile>,		std::add_rvalue_reference_t<int* volatile>			>, "Mismatch with STD 0E");
			check(std::is_same_v<	flx::add_rvalue_reference<int* const volatile>,	std::add_rvalue_reference_t<int* const volatile>	>, "Mismatch with STD 0F");
			check(std::is_same_v<	flx::add_rvalue_reference<void*>,				std::add_rvalue_reference_t<void*>					>, "Mismatch with STD 10");
			check(std::is_same_v<	flx::add_rvalue_reference<const void*>,			std::add_rvalue_reference_t<const void*>			>, "Mismatch with STD 11");

			// arrays
			check(std::is_same_v<	flx::add_rvalue_reference<int[5]>,				std::add_rvalue_reference_t<int[5]>					>, "Mismatch with STD 12");
			check(std::is_same_v<	flx::add_rvalue_reference<const int[5]>,		std::add_rvalue_reference_t<const int[5]>			>, "Mismatch with STD 13");
			check(std::is_same_v<	flx::add_rvalue_reference<int(&)[5]>,			std::add_rvalue_reference_t<int(&)[5]>				>, "Mismatch with STD 14");
			check(std::is_same_v<	flx::add_rvalue_reference<int(&&)[5]>,			std::add_rvalue_reference_t<int(&&)[5]>				>, "Mismatch with STD 15");

			// function types
			check(std::is_same_v<	flx::add_rvalue_reference<int()>,				std::add_rvalue_reference_t<int()>					>, "Mismatch with STD 16");
			check(std::is_same_v<	flx::add_rvalue_reference<int(&)()>,			std::add_rvalue_reference_t<int(&)()>				>, "Mismatch with STD 17");
			check(std::is_same_v<	flx::add_rvalue_reference<int(&&)()>,			std::add_rvalue_reference_t<int(&&)()>				>, "Mismatch with STD 18");
			check(std::is_same_v<	flx::add_rvalue_reference<int(*)(int)>,			std::add_rvalue_reference_t<int(*)(int)>			>, "Mismatch with STD 19");
			check(std::is_same_v<	flx::add_rvalue_reference<int(&)(int)>,			std::add_rvalue_reference_t<int(&)(int)>			>, "Mismatch with STD 1A");
			check(std::is_same_v<	flx::add_rvalue_reference<int(&&)(int)>,		std::add_rvalue_reference_t<int(&&)(int)>			>, "Mismatch with STD 1B");

			// void 
			check(std::is_same_v<	flx::add_rvalue_reference<void>,				std::add_rvalue_reference_t<void>					>, "Mismatch with STD 1C");
			check(std::is_same_v<	flx::add_rvalue_reference<const void>,			std::add_rvalue_reference_t<const void>				>, "Mismatch with STD 1D");
			check(std::is_same_v<	flx::add_rvalue_reference<volatile void>,		std::add_rvalue_reference_t<volatile void>			>, "Mismatch with STD 1E");
			check(std::is_same_v<	flx::add_rvalue_reference<const volatile void>,	std::add_rvalue_reference_t<const volatile void>	>, "Mismatch with STD 1F");

			// enum
			check(std::is_same_v<	flx::add_rvalue_reference<enum E>,				std::add_rvalue_reference_t<enum E>					>, "Mismatch with STD 20");
			check(std::is_same_v<	flx::add_rvalue_reference<enum E&>,				std::add_rvalue_reference_t<enum E&>				>, "Mismatch with STD 21");
			check(std::is_same_v<	flx::add_rvalue_reference<enum E&&>,			std::add_rvalue_reference_t<enum E&&>				>, "Mismatch with STD 22");

			subgroup = "NULL";
		}



	}
} // namespace test