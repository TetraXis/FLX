#include <iostream>
#include <vector>

//#include "flx_dynamic_array.hpp"
#include "flx_unique_ptr.hpp"
#include "flx_dynamic_array.hpp"

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

using test_t = std::vector<test_str>;
//using test_t = flx::dynamic_array<test_str>;

int main()
{
	test_t a;

	for (size_t i = 0; i < 20; i++)
	{
		a.emplace_back();
	}

	std::cout << a[19].a;
}