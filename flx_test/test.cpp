#include <iostream>
#include <vector>
#include <sstream>

//#include "flx_dynamic_array.hpp"
#include "flx_unique_ptr.hpp"
#include "flx_dynamic_array.hpp"

#define META_TESTS 10
#define TESTS 10'000'000

struct test_str
{
	int a = 10;

	test_str()
	{
	}

	~test_str()
	{
	}

	//test_str(test_str&&) = default;
};

using namespace flx;

//using test_t = std::vector<test_str>;
using test_t = flx::dynamic_array<test_str>;

#include "D:\C++\Tools\timer.h"

int main()
{
	std::stringstream SS;
	std::stringstream ss;
	u64 sum = 0;

	for (size_t II = 0; II < META_TESTS; II++)
	{


		timer t;

		t.start();
		for (size_t I = 0; I < TESTS; I++)
		{
			test_t a;

			for (size_t i = 0; i < 20; i++)
			{
				a.emplace_back();
			}

			ss << a[19].a;
		}
		t.stop();
		
		SS << t.elapsed_milliseconds() << "ms.\n";
		sum += t.elapsed_milliseconds();
	}

	std::cout << ss.str() << '\n';
	std::cout << SS.str() << '\n';

	std::cout << "AVG:\n";
	std::cout << f64(sum) / META_TESTS << '\n';

}

/*

std::vector 436ms
flx::dynamic_array 228ms

std::vector 4330.4ms
flx::dynamic_array 2675.0ms

*/