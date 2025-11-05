#include "flx/imp_core.hpp"
#include "flx/new.hpp"
#include "flx/utility.hpp"
#include "flx/type_traits.hpp"
#include "flx/concepts.hpp"
#include "flx/memory.hpp"
#include "flx/dynamic_array.hpp"

#include "flx_tests.hpp"
#include "test_h.h"

#include <iostream>
#include <vector>
#include <memory>
//#include <algorithm>

//using namespace flx;
using namespace flx::types;

template<typename ty>
struct test_all
{
	using value_type = ty;

	ty* allocate(unsigned long long)
	{
		return nullptr;
	}

	void deallocate(ty*)
	{
		return;
	}

	void deallocate(ty*, szt)
	{
		return;
	}
};

constexpr int test_f()
{
	int result{};

	flx::default_raw_allocator<int> a;
	int* p = a.allocate(10);

	flx::construct_at(&p[0], flx::nothrow, 5);
	flx::construct_at(&p[1], flx::nothrow, 15);
	flx::construct_at(&p[2], flx::nothrow, 25);

	result = p[1];

	a.deallocate(p);

	return result;
}

int main()
{
	constexpr int result = test_f();

	return result;

	//flx::test::test_flx();
	//
	//std::cout << flx::test::output.str();

	return 0;
}