#include "flx/imp_core.hpp"
#include "flx/new.hpp"
#include "flx/utility.hpp"
#include "flx/type_traits.hpp"
#include "flx/concepts.hpp"
#include "flx/dynamic_array.hpp"

#include "flx_tests.hpp"

#include <iostream>
#include <vector>
//#include <algorithm>

//using namespace flx;

int main()
{
	flx::test::test_flx();

	std::cout << flx::test::output.str();

	return 0;
}