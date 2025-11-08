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

constexpr void* std_new(size_t n) noexcept
{
	return new char[n]; 
	//return ::operator new(n);
}

constexpr void std_del(void* ptr) noexcept
{
	delete[] ptr;
	//::operator delete(ptr);
}

constexpr int res()
{
	auto a = std_new(10);
	std_del(a);
	return 10;
}

constexpr int test_al()
{
	flx::default_raw_allocator<int> al{};

	int* a = al.allocate(10);
	al.deallocate(a);

	return 10;
}

int main()
{
	constexpr int n = test_al();

	return 0;
}