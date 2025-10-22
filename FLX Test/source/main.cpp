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

int main()
{
	flx::test::test_flx();

	std::cout << flx::test::output.str();

	return 0;
}