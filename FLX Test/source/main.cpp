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

void test_f()
{

}

int main()
{
	/*std::allocator<int>;

	flx::dynamic_array<int>;*/

	flx::test::test_flx();

	std::cout << flx::test::output.str();

	return 0;
}