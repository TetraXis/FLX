#include "flx_tests.hpp"

#include "flx/imp_core.hpp"
#include "flx/new.hpp"
#include "flx/type_traits.hpp"
#include "flx/concepts.hpp"
#include "flx/utility.hpp"
#include "flx/dynamic_array.hpp"

#include <sstream>

using namespace flx;

std::stringstream test::output{};
u64 test::tests_passed = 0;
u64 test::tests_failed = 0;

bool test::test_flx()
{
	if constexpr (IMP_FLX_CONFIGURATION_ == IMP_FLX_CONFIGURATION_RELEASE_)
	{
		output << "Test is running in RELEASE.\n";
		output << "Test is running in RELEASE.\n";
		output << "Test is running in RELEASE.\n";
	}

	if constexpr (IMP_FLX_CONFIGURATION_ == IMP_FLX_CONFIGURATION_DEBUG_)
	{
		output << "Test is running in DEBUG.\n";
	}

	bool result = false;

	output << "\nTesting dynamic_array...\n";
	result = test_dynamic_array();
	output << (result ? "dynamic_array PASSED.\n\n" : "dynamic_array FAILED.\n\n");

	output << "\nTest finihsed.\n";
	output << "Tests done:\t" << tests_passed + tests_failed << ".\n";
	output << "Tests passed:\t" << tests_passed << ".\n";
	output << "Tests failed:\t" << tests_failed << ".\n";

	return tests_failed == 0;
}

bool test::test_new()
{
	return true;
}

bool test::test_type_traits()
{
	return true;
}

bool test::test_concepts()
{
	return true;
}

bool test::test_utility()
{
	return true;
}

bool test::test_dynamic_array()
{
	bool result = true;

	output << ".\tTesting constructon with primitive types...\n";

	// default constructor
	try
	{
		dynamic_array<i32> a{};
		dynamic_array<f32> b{};
		dynamic_array<b08> c{};
		dynamic_array<u64> d{};

		if (a.capacity_ != dynamic_array<i32>::PREALLOCATED_CAPACITY) throw;
		if (b.capacity_ != dynamic_array<f32>::PREALLOCATED_CAPACITY) throw;
		if (c.capacity_ != dynamic_array<b08>::PREALLOCATED_CAPACITY) throw;
		if (d.capacity_ != dynamic_array<u64>::PREALLOCATED_CAPACITY) throw;

		if (a.size_ != 0) throw;
		if (b.size_ != 0) throw;
		if (c.size_ != 0) throw;
		if (d.size_ != 0) throw;

		output << ".\t.\tPASSED Default constructor.\n";
		tests_passed++;
	}
	catch (...)
	{
		output << ".\t.\tFAILED Default constructor.\n";
		result = false;
		tests_failed++;
	}

	// copy constructor
	try
	{
		dynamic_array<i32> a{};
		dynamic_array<f32> b{};
		dynamic_array<b08> c{};
		dynamic_array<u64> d{};

		dynamic_array<i32> a1{ a };
		dynamic_array<f32> b1{ b };
		dynamic_array<b08> c1{ c };
		dynamic_array<u64> d1{ d };

		if (a.capacity_ != a1.capacity_) throw;
		if (b.capacity_ != b1.capacity_) throw;
		if (c.capacity_ != c1.capacity_) throw;
		if (d.capacity_ != d1.capacity_) throw;

		if (a.size_ != a1.size_) throw;
		if (b.size_ != b1.size_) throw;
		if (c.size_ != c1.size_) throw;
		if (d.size_ != d1.size_) throw;

		output << ".\t.\tPASSED Copy constructor.\n";
		tests_passed++;
	}
	catch (...)
	{
		output << ".\t.\tFAILED Copy constructor.\n";
		result = false;
		tests_failed++;
	}

	return result;
}
