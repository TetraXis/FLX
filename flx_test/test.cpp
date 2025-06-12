#include <iostream>
#include <vector>

//#include "flx_dynamic_array.hpp"
#include "flx_unique_ptr.hpp"
#include "flx_dynamic_array.hpp"

struct test_str
{
	test_str()
	{
		std::cout << "Con\n";
	}

	~test_str()
	{
		std::cout << "Des\n";
	}

	test_str(test_str&&) = default;
};

using namespace flx;

using test_t = std::vector<test_str>;

int main()
{
	test_str* b = new test_str[10];

	test_t a;

	for (size_t i = 0; i < 20; i++)
	{
		a.emplace_back();
		std::cout << i << '\n';
	}
}