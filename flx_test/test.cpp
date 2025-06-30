#include <iostream>
#include <vector>
#include <sstream>
#include <type_traits>
#include <string>
#include <unordered_set>
#include <map>

#define FLX_ALL_MEMBERS_ARE_PUBLIC

#include "flx_unique_ptr.hpp"
#include "flx_dynamic_array.hpp"

using namespace flx;

#define META_TESTS 10
#define TESTS 10'000'000

struct test_str
{
	int a = 0;
	//int* data;

	//test_str() noexcept = default;
	//{
	//	data = new int[10];
	//}

	//test_str(test_str&& other) noexcept = default;
	//	:data(other.data)
	//{
	//	other.data = nullptr;
	//}

	//~test_str() noexcept = default;
	//{
	//	delete[] data;
	//}

	//test_str(test_str&&) = default;
};
using test_t_std = std::vector			< test_str >;
using test_t_flx = flx::dynamic_array	< test_str >;


using test_t = std::vector<test_str>;
//using test_t = flx::dynamic_array<test_str>;

#include "D:\C++\Tools\timer.h"

int main()
{
	//flx::dynamic_array<flx::unique_ptr<int>> a;
	//
	//a.emplace_back(new int(1));
	//a.emplace_back(new int(1));
	//a.emplace_back(new int(1));
	//a.emplace_back(new int(1));
	//a.emplace_back(new int(1));
	//a.emplace_back(new int(1));
}