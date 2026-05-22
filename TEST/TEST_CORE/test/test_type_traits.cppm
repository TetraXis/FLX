module;

#include <type_traits>
#include <string>
#include <functional>

export module test.type_traits;

import test.core;
import flx.type_traits;

export namespace test
{
	inline void type_traits()
	{
		group = "type_traits.hpp";

		enum E { dummy };

		struct incomplete;

		struct abstract 
		{ 
			virtual void f() = 0; 
		};

		struct move_only
		{
			move_only()								= default;
			move_only(move_only&&)					= default;
			move_only& operator=(move_only&&)		= default;
			move_only& operator=(const move_only&)	= delete;
			move_only(const move_only&)				= delete;
		};



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



		// ===== declval ===== //
		{
			subgroup = "declval";

			// return type
			{
				// fundamental
				check(std::is_same_v<	decltype(flx::declval<int>()),					decltype(std::declval<int>())					>,	"Return type mismatch with STD 00");
				check(std::is_same_v<	decltype(flx::declval<const int>()),			decltype(std::declval<const int>())				>,	"Return type mismatch with STD 01");
				check(std::is_same_v<	decltype(flx::declval<volatile int>()),			decltype(std::declval<volatile int>())			>,	"Return type mismatch with STD 02");
				check(std::is_same_v<	decltype(flx::declval<const volatile int>()),	decltype(std::declval<const volatile int>())	>,	"Return type mismatch with STD 03");

				// lvalue references
				check(std::is_same_v<	decltype(flx::declval<int&>()),					decltype(std::declval<int&>())					>,	"Return type mismatch with STD 04");
				check(std::is_same_v<	decltype(flx::declval<const int&>()),			decltype(std::declval<const int&>())			>,	"Return type mismatch with STD 05");
				check(std::is_same_v<	decltype(flx::declval<volatile int&>()),		decltype(std::declval<volatile int&>())			>,	"Return type mismatch with STD 06");
				check(std::is_same_v<	decltype(flx::declval<const volatile int&>()),	decltype(std::declval<const volatile int&>())	>,	"Return type mismatch with STD 07");

				// rvalue references
				check(std::is_same_v<	decltype(flx::declval<int&&>()),				decltype(std::declval<int&&>())					>,	"Return type mismatch with STD 08");
				check(std::is_same_v<	decltype(flx::declval<const int&&>()),			decltype(std::declval<const int&&>())			>,	"Return type mismatch with STD 09");

				// pointers
				check(std::is_same_v<	decltype(flx::declval<int*>()),					decltype(std::declval<int*>())					>,	"Return type mismatch with STD 0A");
				check(std::is_same_v<	decltype(flx::declval<const int*>()),			decltype(std::declval<const int*>())			>,	"Return type mismatch with STD 0B");
				check(std::is_same_v<	decltype(flx::declval<int* const>()),			decltype(std::declval<int* const>())			>,	"Return type mismatch with STD 0C");

				// arrays
				check(std::is_same_v<	decltype(flx::declval<int[5]>()),				decltype(std::declval<int[5]>())				>,	"Return type mismatch with STD 0D");
				check(std::is_same_v<	decltype(flx::declval<const int[5]>()),			decltype(std::declval<const int[5]>())			>,	"Return type mismatch with STD 0E");

				// function types
				check(std::is_same_v<	decltype(flx::declval<int()>()),				decltype(std::declval<int()>())					>,	"Return type mismatch with STD 0F");
				check(std::is_same_v<	decltype(flx::declval<int(*)(int)>()),			decltype(std::declval<int(*)(int)>())			>,	"Return type mismatch with STD 10");

				// void
				check(std::is_same_v<	decltype(flx::declval<void>()),					decltype(std::declval<void>())					>,	"Return type mismatch with STD 11");

				// enum
				check(std::is_same_v<	decltype(flx::declval<E>()),					decltype(std::declval<E>())						>,	"Return type mismatch with STD 12");

				// incomplete type
				check(std::is_same_v<	decltype(flx::declval<incomplete>()),			decltype(std::declval<incomplete>())			>,	"Return type mismatch with STD 13");
				
				// abstract type
				check(std::is_same_v<	decltype(flx::declval<abstract>()),				decltype(std::declval<abstract>())				>,	"Return type mismatch with STD 14");
				
				// move_only type
				check(std::is_same_v<	decltype(flx::declval<move_only>()),			decltype(std::declval<move_only>())				>,	"Return type mismatch with STD 15");
				
				// function reference type
				check(std::is_same_v<	decltype(flx::declval<int(&)()>()),				decltype(std::declval<int(&)()>())				>,	"Return type mismatch with STD 16");
				
				// volatile rvalue reference
				check(std::is_same_v<	decltype(flx::declval<volatile int&&>()),		decltype(std::declval<volatile int&&>())		>,	"Return type mismatch with STD 17");
				
				// array of unknown bound
				check(std::is_same_v<	decltype(flx::declval<int[]>()),				decltype(std::declval<int[]>())					>,	"Return type mismatch with STD 18");
				
				// cv-qualified array of unknown bound
				check(std::is_same_v<	decltype(flx::declval<const int[]>()),			decltype(std::declval<const int[]>())			>,	"Return type mismatch with STD 19");
				check(std::is_same_v<	decltype(flx::declval<volatile int[]>()),		decltype(std::declval<volatile int[]>())		>,	"Return type mismatch with STD 1A");
				check(std::is_same_v<	decltype(flx::declval<const volatile int[]>()),	decltype(std::declval<const volatile int[]>())	>,	"Return type mismatch with STD 1B");
			}

			check(noexcept(flx::declval<int>()), "declval must be noexcept 00");

			static_assert(std::is_same_v<decltype(flx::declval<int>()), int&&>, "declval must be constexpr 00");

			// calling declval should be ill-formed
			// check(flx::declval<int>(),	"declval was incorrectly allowed in an evaluated context 00");

			subgroup = "NULL";
		}



		// ===== forward ===== //
		{
		    subgroup = "forward";
		
		    // fundamental types
		    check(std::is_same_v<	decltype(flx::forward<int>(0)),						decltype(std::forward<int>(0))						>,	"Return type mismatch with STD 00");
		    check(std::is_same_v<	decltype(flx::forward<const int>(0)),				decltype(std::forward<const int>(0))				>,	"Return type mismatch with STD 01");
		    check(std::is_same_v<	decltype(flx::forward<volatile int>(0)),			decltype(std::forward<volatile int>(0))				>,	"Return type mismatch with STD 02");
		    check(std::is_same_v<	decltype(flx::forward<const volatile int>(0)),		decltype(std::forward<const volatile int>(0))		>,	"Return type mismatch with STD 03");
		
		    // lvalue references
		    int lval = 42;
		    check(std::is_same_v<	decltype(flx::forward<int&>(lval)),					decltype(std::forward<int&>(lval))					>,	"Return type mismatch with STD 04");
		    check(std::is_same_v<	decltype(flx::forward<const int&>(lval)),			decltype(std::forward<const int&>(lval))			>,	"Return type mismatch with STD 05");
		    check(std::is_same_v<	decltype(flx::forward<volatile int&>(lval)),		decltype(std::forward<volatile int&>(lval))			>,	"Return type mismatch with STD 06");
		    check(std::is_same_v<	decltype(flx::forward<const volatile int&>(lval)),	decltype(std::forward<const volatile int&>(lval))	>,	"Return type mismatch with STD 07");
		
		    // value references
		    check(std::is_same_v<	decltype(flx::forward<int&&>(0)),					decltype(std::forward<int&&>(0))					>,	"Return type mismatch with STD 08");
		    check(std::is_same_v<	decltype(flx::forward<const int&&>(0)),				decltype(std::forward<const int&&>(0))				>,	"Return type mismatch with STD 09");
		    check(std::is_same_v<	decltype(flx::forward<volatile int&&>(0)),			decltype(std::forward<volatile int&&>(0))			>,	"Return type mismatch with STD 0A");
		    check(std::is_same_v<	decltype(flx::forward<const volatile int&&>(0)),	decltype(std::forward<const volatile int&&>(0))		>,	"Return type mismatch with STD 0B");
		
		    // pointers
			int* ptr = &lval;
			int* const ptr_const = ptr;
			const int* const_ptr = ptr;
			const int* const const_ptr_const = ptr;
			
			check(std::is_same_v<	decltype(flx::forward<int*>(ptr)),							decltype(std::forward<int*>(ptr))							>,	"Return type mismatch with STD 0C");
			check(std::is_same_v<	decltype(flx::forward<const int*>(const_ptr)),				decltype(std::forward<const int*>(const_ptr))				>,	"Return type mismatch with STD 0D");
			check(std::is_same_v<	decltype(flx::forward<int* const>(ptr_const)),				decltype(std::forward<int* const>(ptr_const))				>,	"Return type mismatch with STD 0E");
			check(std::is_same_v<	decltype(flx::forward<const int* const>(const_ptr_const)),	decltype(std::forward<const int* const>(const_ptr_const))	>,	"Return type mismatch with STD 0F");
		
		    // arrays
		    int arr[5] = {};
		    check(std::is_same_v<	decltype(flx::forward<int[5]>(arr)),				decltype(std::forward<int[5]>(arr))					>,	"Return type mismatch with STD 10");
		    check(std::is_same_v<	decltype(flx::forward<const int[5]>(arr)),			decltype(std::forward<const int[5]>(arr))			>,	"Return type mismatch with STD 11");
		
		    // function types
			auto fn_lambda = []() { return 0; };
			using func_ptr_type = int(*)();
			func_ptr_type fn_ptr = +fn_lambda;
			int (&fn_ref)() = *fn_ptr;
			
			check(std::is_same_v<	decltype(flx::forward<func_ptr_type>(fn_ptr)),		decltype(std::forward<func_ptr_type>(fn_ptr))		>,	"Return type mismatch with STD 12");
			check(std::is_same_v<	decltype(flx::forward<int(&)()>(fn_ref)),			decltype(std::forward<int(&)()>(fn_ref))			>,	"Return type mismatch with STD 13");
			check(std::is_same_v<	decltype(flx::forward<int()>(*fn_ptr)),				decltype(std::forward<int()>(*fn_ptr))				>,	"Return type mismatch with STD 14"); // decays to pointer

		    // enum
		    enum E { E0 };
		    E e = E0;
		    check(std::is_same_v<	decltype(flx::forward<E>(e)),						decltype(std::forward<E>(e))						>,	"Return type mismatch with STD 15");
		    check(std::is_same_v<	decltype(flx::forward<E&>(e)),						decltype(std::forward<E&>(e))						>,	"Return type mismatch with STD 16");
		
		    // incomplete type
		    incomplete* inc = nullptr;
		    check(std::is_same_v<	decltype(flx::forward<incomplete*>(inc)),			decltype(std::forward<incomplete*>(inc))			>,	"Return type mismatch with STD 17");
		
		    // abstract type
		    abstract* ab = nullptr;
		    check(std::is_same_v<	decltype(flx::forward<abstract*>(ab)),				decltype(std::forward<abstract*>(ab))				>,	"Return type mismatch with STD 18");
		
		    // move‑only type
		    move_only mo;
		    check(std::is_same_v<	decltype(flx::forward<move_only>(std::move(mo))),	decltype(std::forward<move_only>(std::move(mo)))	>,	"Return type mismatch with STD 19");
		    check(std::is_same_v<	decltype(flx::forward<move_only&>(mo)),				decltype(std::forward<move_only&>(mo))				>,	"Return type mismatch with STD 1A");
		
		    // array of unknown bound
		    int arr_unknown[] = { 1,2,3 };
		    check(std::is_same_v<	decltype(flx::forward<int[]>(arr_unknown)),			decltype(std::forward<int[]>(arr_unknown))			>,	"Return type mismatch with STD 1B");
		
		    // cv‑qualified array of unknown bound
		    const int arr_const_unknown[]		= { 1,2,3 };
		    volatile int arr_vol_unknown[]		= { 1,2,3 };
		    const volatile int arr_cv_unknown[]	= { 1,2,3 };
		    check(std::is_same_v<	decltype(flx::forward<const int[]>(arr_const_unknown)),			decltype(std::forward<const int[]>(arr_const_unknown))			>,	"Return type mismatch with STD 1C");
		    check(std::is_same_v<	decltype(flx::forward<volatile int[]>(arr_vol_unknown)),		decltype(std::forward<volatile int[]>(arr_vol_unknown))			>,	"Return type mismatch with STD 1D");
		    check(std::is_same_v<	decltype(flx::forward<const volatile int[]>(arr_cv_unknown)),	decltype(std::forward<const volatile int[]>(arr_cv_unknown))	>,	"Return type mismatch with STD 1E");
		
		    // reference to function
			auto fn_ptr2 = +[]() { return 0; };
			int(&func_ref)() = *fn_ptr2;
			check(std::is_same_v<	decltype(flx::forward<int(&)()>(func_ref)),			decltype(std::forward<int(&)()>(func_ref))			>,	"Return type mismatch with STD 1F");

		    // void must be ill-formed
		 // check(std::is_same_v<	decltype(flx::forward<void>(void())),				decltype(std::forward<void>(void()))				>,	"Return type mismatch with STD 20");

			// edge case for int(&)[]
			int(&ref_unknown)[] = arr_unknown;
			check(std::is_same_v<	decltype(flx::forward<int(&)[]>(ref_unknown)),		decltype(std::forward<int(&)[]>(ref_unknown))		>,	"Return type mismatch with STD 21");

			// noexcept function types
			auto lambda_noexcept = []() noexcept { return 0; };
			using func_ptr = int(*)() noexcept;
			check(std::is_same_v<	decltype(flx::forward<func_ptr>(+lambda_noexcept)),	decltype(std::forward<func_ptr>(+lambda_noexcept))	>,	"Return type mismatch with STD 22");

			// deducing ty
			constexpr auto forward_wrapper = [](auto&& arg) constexpr -> decltype(auto)
			{
				return flx::forward<decltype(arg)>(arg);
			};
			int x = 42;
			check(std::is_same_v<decltype(forward_wrapper(x)), int&>, "ty deduction failure 00");
			check(std::is_same_v<decltype(forward_wrapper(42)), int&&>, "ty deduction failure 01");

		    // noexcept
		    check(noexcept(flx::forward<int>(0)), "forward must be noexcept 00");

			// constexpr check
			// if this fails to compile, forward isn't constexpr
			constexpr int result = []() constexpr -> int
			{
				int x = 42;
				return flx::forward<int&>(x);
			}();
			check(result == 42, "forward must be constexpr 00");
		
			struct bitfield_struct
			{
				int bf : 1;
			};
			bitfield_struct s = { 0 };

		    // must be ill‑formed
		    // flx::forward<int[5]>(0);		// array argument must be array lvalue
			// flx::forward<int&>(s.bf);	// bit‑field: cannot form reference
		
		    subgroup = "NULL";
		}



		// ===== move ===== //
		{
		    subgroup = "move";
		
		    // fundamental types
		    check(std::is_same_v<	decltype(flx::move(0)),								decltype(std::move(0))								>,	"Return type mismatch with STD 00");
		    check(std::is_same_v<	decltype(flx::move(::std::declval<int>())),			decltype(::std::move(::std::declval<int>()))		>,	"Return type mismatch with STD 01");
		    check(std::is_same_v<	decltype(flx::move(::std::declval<const int>())),	decltype(::std::move(::std::declval<const int>()))	>,	"Return type mismatch with STD 02");
		
		    // lvalues
		    int lval = 42;
		    const int clval = 42;
		    volatile int vlval = 42;
		    const volatile int cvlval = 42;
		    check(std::is_same_v<	decltype(flx::move(lval)),					decltype(std::move(lval))					>,	"Return type mismatch with STD 03");
		    check(std::is_same_v<	decltype(flx::move(clval)),					decltype(std::move(clval))					>,	"Return type mismatch with STD 04");
		    check(std::is_same_v<	decltype(flx::move(vlval)),					decltype(std::move(vlval))					>,	"Return type mismatch with STD 05");
		    check(std::is_same_v<	decltype(flx::move(cvlval)),				decltype(std::move(cvlval))					>,	"Return type mismatch with STD 06");
		
		    // rvalues
		    check(std::is_same_v<	decltype(flx::move(42)),					decltype(std::move(42))						>,	"Return type mismatch with STD 07");
		    // xvalues
		    check(std::is_same_v<	decltype(flx::move(std::move(lval))),		decltype(std::move(std::move(lval)))		>,	"Return type mismatch with STD 08");
		
		    // nullptr_t
		    std::nullptr_t np = nullptr;
		    check(std::is_same_v<	decltype(flx::move(np)),					decltype(std::move(np))						>,	"Return type mismatch with STD 09");
		
		    // pointers
		    int* ptr = &lval;
		    const int* cptr = ptr;
		    int* const ptr_const = ptr;
		    const int* const cptr_const = ptr;
		    check(std::is_same_v<	decltype(flx::move(ptr)),					decltype(std::move(ptr))					>,	"Return type mismatch with STD 0A");
		    check(std::is_same_v<	decltype(flx::move(cptr)),					decltype(std::move(cptr))					>,	"Return type mismatch with STD 0B");
		    check(std::is_same_v<	decltype(flx::move(ptr_const)),				decltype(std::move(ptr_const))				>,	"Return type mismatch with STD 0C");
		    check(std::is_same_v<	decltype(flx::move(cptr_const)),			decltype(std::move(cptr_const))				>,	"Return type mismatch with STD 0D");
		
		    // arrays
		    int arr[5] = {};
		    const int carr[5] = {};
		    volatile int varr[5] = {};
		    const volatile int cvarr[5] = {};
		    check(std::is_same_v<	decltype(flx::move(arr)),					decltype(std::move(arr))					>,	"Return type mismatch with STD 0E");
		    check(std::is_same_v<	decltype(flx::move(carr)),					decltype(std::move(carr))					>,	"Return type mismatch with STD 0F");
		    check(std::is_same_v<	decltype(flx::move(varr)),					decltype(std::move(varr))					>,	"Return type mismatch with STD 10");
		    check(std::is_same_v<	decltype(flx::move(cvarr)),					decltype(std::move(cvarr))					>,	"Return type mismatch with STD 11");
		
		    // array of unknown bound
		    int arr_unknown[] = {1,2,3};
		    const int carr_unknown[] = {1,2,3};
		    volatile int varr_unknown[] = {1,2,3};
		    const volatile int cvarr_unknown[] = {1,2,3};
		    check(std::is_same_v<	decltype(flx::move(arr_unknown)),			decltype(std::move(arr_unknown))			>,	"Return type mismatch with STD 12");
		    check(std::is_same_v<	decltype(flx::move(carr_unknown)),			decltype(std::move(carr_unknown))			>,	"Return type mismatch with STD 13");
		    check(std::is_same_v<	decltype(flx::move(varr_unknown)),			decltype(std::move(varr_unknown))			>,	"Return type mismatch with STD 14");
		    check(std::is_same_v<	decltype(flx::move(cvarr_unknown)),			decltype(std::move(cvarr_unknown))			>,	"Return type mismatch with STD 15");
		
		    // reference to array of unknown bound
		    int(&ref_unknown)[] = arr_unknown;
		    const int(&cref_unknown)[] = carr_unknown;
		    check(std::is_same_v<	decltype(flx::move(ref_unknown)),			decltype(std::move(ref_unknown))			>,	"Return type mismatch with STD 16");
		    check(std::is_same_v<	decltype(flx::move(cref_unknown)),			decltype(std::move(cref_unknown))			>,	"Return type mismatch with STD 17");
		
		    // function types
		    auto fn_lambda = []() { return 0; };
		    using FnPtr = int(*)();
		    FnPtr fn_ptr = +fn_lambda;
		    int(&fn_ref)() = *fn_ptr;
		    check(std::is_same_v<	decltype(flx::move(fn_ptr)),				decltype(std::move(fn_ptr))					>,	"Return type mismatch with STD 18");
		    check(std::is_same_v<	decltype(flx::move(fn_ref)),				decltype(std::move(fn_ref))					>,	"Return type mismatch with STD 19");
		    check(std::is_same_v<	decltype(flx::move(*fn_ptr)),				decltype(std::move(*fn_ptr))				>,	"Return type mismatch with STD 1A"); // function lvalue
		
		    // noexcept function types
		    auto noexcept_lambda = []() noexcept { return 0; };
		    using NoexceptFnPtr = int(*)() noexcept;
		    NoexceptFnPtr noexcept_ptr = +noexcept_lambda;
		    check(std::is_same_v<	decltype(flx::move(noexcept_ptr)),			decltype(std::move(noexcept_ptr))			>,	"Return type mismatch with STD 1B");
		
		    // enum
		    E e = dummy;
		    check(std::is_same_v<	decltype(flx::move(e)),						decltype(std::move(e))						>,	"Return type mismatch with STD 1C");
		
		    // incomplete type
		    incomplete* inc = nullptr;
		    check(std::is_same_v<	decltype(flx::move(inc)),					decltype(std::move(inc))					>,	"Return type mismatch with STD 1D");
		
		    // abstract type
		    abstract* ab = nullptr;
		    check(std::is_same_v<	decltype(flx::move(ab)),					decltype(std::move(ab))						>,	"Return type mismatch with STD 1E");
		
		    // move‑only type
		    move_only mo;
		    check(std::is_same_v<	decltype(flx::move(move_only())),			decltype(std::move(move_only()))			>,	"Return type mismatch with STD 1F");
		    check(std::is_same_v<	decltype(flx::move(mo)),					decltype(std::move(mo))						>,	"Return type mismatch with STD 20");
		    check(std::is_same_v<	decltype(flx::move(std::move(mo))),			decltype(std::move(std::move(mo)))			>,	"Return type mismatch with STD 21");
		
		    // deduction wrapper (forwarding reference)
		    constexpr auto move_wrapper = [](auto&& arg) constexpr -> decltype(auto)
			{
		        return flx::move(arg);
		    };
		    int x = 42;
		    const int cx = 42;
		    volatile int vx = 42;
		    const volatile int cvx = 42;
		    check(std::is_same_v<	decltype(move_wrapper(x)),		int&&>,					"Deduction failure: lvalue as rvalue 00");
		    check(std::is_same_v<	decltype(move_wrapper(42)),		int&&>,					"Deduction failure: rvalue as rvalue 01");
		    check(std::is_same_v<	decltype(move_wrapper(cx)),		const int&&>,			"Deduction failure: const lvalue 02");
		    check(std::is_same_v<	decltype(move_wrapper(vx)),		volatile int&&>,		"Deduction failure: volatile lvalue 03");
		    check(std::is_same_v<	decltype(move_wrapper(cvx)),	const volatile int&&>,	"Deduction failure: cv lvalue 04");
		
		    // noexcept check
		    check(noexcept(flx::move(0)),		"move must be noexcept 00");
		    check(noexcept(flx::move(lval)),	"move must be noexcept 01");
		
		    // constexpr check
		    constexpr int result = []() constexpr -> int
			{
		        int a = 42;
		        return flx::move(a);
		    }();
		    check(result == 42, "move must be constexpr 00");
		
		    // ill‑formed
		    // struct bitfield { int bf : 1; } bf;
		    // flx::move(bf.bf);
		    // flx::move(void());
		    // flx::move(flx::declval<void>());
		    // flx::move(std::declval<void>());
		
		    subgroup = "NULL";
		}
	}
} // namespace test