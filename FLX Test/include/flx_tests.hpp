#ifndef FLX_TESTS_HPP
#define FLX_TESTS_HPP

#define FLX_ALL_MEMBERS_ARE_PUBLIC

#include "flx/imp_core.hpp"

#include <sstream>

FLX_BEGIN_

namespace test
{
	FLX_API_ extern std::stringstream output;
	FLX_API_ extern u64 tests_passed;
	FLX_API_ extern u64 tests_failed;

	FLX_API_ bool test_flx();
	
	FLX_API_ bool test_new();
	FLX_API_ bool test_type_traits();
	FLX_API_ bool test_concepts();
	FLX_API_ bool test_utility();
	FLX_API_ bool test_dynamic_array();
}

FLX_END_

#endif // FLX_TESTS_HPP