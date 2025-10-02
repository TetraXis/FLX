//#include <iostream>

#include <vector>
#include <algorithm>

#include "flx/imp_core.hpp"
#include "flx/new.hpp"
#include "flx/utility.hpp"
#include "flx/type_traits.hpp"
#include "flx/concepts.hpp"
#include "flx/dynamic_array.hpp"

//using namespace flx;

#include <malloc.h>  // MSVC specific, but not STL
//
//void test() noexcept
//{
//	int* a = static_cast<int*>(_malloc_base(sizeof(int)));  // Raw heap alloc
//
//	if (a) {
//		*a = 5;
//		_free_base(a);
//	}
//}
//
//
//struct test_str
//{
//	int* data;
//
//	constexpr test_str()
//	{
//		data = new int;
//	}
//
//	constexpr ~test_str()
//	{
//		delete data;
//	}
//};

constexpr int test()
{
	//std::vector<int> a;
	flx::dynamic_array<int> a;

	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);

	return a[2];
}

//__declspec(allocator) char* allocate_string() {
//	return new char[100];  
//}

int main()
{
	constexpr int balls = test();

	return balls;
}