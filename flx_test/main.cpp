#include <iostream>
#include <vector>

//#include "flx_dynamic_array.hpp"
#include "flx_unique_ptr.hpp"

using namespace flx;

int main()
{
	unique_ptr<int> a;

	std::cout << a.get();
}