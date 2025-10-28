#include "flx_tests.hpp"

#include "flx/imp_core.hpp"
#include "flx/new.hpp"
#include "flx/type_traits.hpp"
#include "flx/concepts.hpp"
#include "flx/utility.hpp"
#include "flx/dynamic_array.hpp"

#include <sstream>
#include <exception>
#include <limits>
#include <random>
#include <array>

// TODO: tests for dynamic_array iterators
// TODO: consider testing internal functions
// NOTE: we now only test what functions do, but not what they take in

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"

using namespace flx;
using namespace flx::test;

FLX_API_ std::stringstream test::output{};
FLX_API_ std::string test::testee{};
FLX_API_ std::string test::header{};
FLX_API_ std::string test::chunk{};
FLX_API_ u64 test::tests_passed = 0;
FLX_API_ u64 test::tests_failed = 0;

FLX_API_ u64 test::called_def_constructors = 0;
FLX_API_ u64 test::called_custom_constructors = 0;
FLX_API_ u64 test::called_copy_constructors = 0;
FLX_API_ u64 test::called_move_constructors = 0;
FLX_API_ u64 test::called_copy_assigments = 0;
FLX_API_ u64 test::called_move_assigments = 0;
FLX_API_ u64 test::called_destructors = 0;
FLX_API_ std::string test::called_result = "";

FLX_API_ bool test::result_header = true;
FLX_API_ bool test::result_chunk = true;

void test::pass_(const std::string& msg)
{
	output << ".\t" GREEN "PASSED" RESET " " << testee << ": " << msg << ".\n";
	if (called_result != "")
	{
		output << ">\t" << called_result << ".\n";
	}
	tests_passed++;
	//result_chunk = true;
}

void test::pass_()
{
	output << ".\t" GREEN "PASSED" RESET " " << testee << ".\n";
	tests_passed++;
	//result_chunk = true;
}

void test::fail_(const std::string& msg)
{
	output << ".\t" RED "FAILED" RESET " " << testee << ": " << msg << ".\n";
	if (called_result != "")
	{
		output << called_result << ".\n";
	}
	tests_failed++;
	result_header = false;
	result_chunk = false;
}

void test::fail_()
{
	output << ".\t" RED "FAILED" RESET " " << testee << ".\n";
	tests_failed++;
	result_header = false;
	result_chunk = false;
}

void test::header_status_()
{
	if (result_header)
	{
		output << GREEN "PASSED" RESET " " << header << ".\n";
	}
	else
	{
		output << RED "FAILED" RESET " " << header << ".\n";
	}
}

void test::chunk_status_()
{
	if (result_chunk)
	{
		output << ".\t" GREEN "PASSED" RESET " " << chunk << ".\n";
	}
	else
	{
		output << ".\t" RED "FAILED" RESET " " << chunk << ".\n";
	}
}

void test::reset_calls_()
{
	called_def_constructors		= 0;
	called_custom_constructors	= 0;
	called_copy_constructors	= 0;
	called_move_constructors	= 0;
	called_copy_assigments		= 0;
	called_move_assigments		= 0;
	called_destructors			= 0;
}

bool test::test_calls_
(
	u64 expected_called_def_constructors	= 0,
	u64 expected_called_custom_constructors	= 0,
	u64 expected_called_copy_constructors	= 0,
	u64 expected_called_move_constructors	= 0,
	u64 expected_called_copy_assigments		= 0,
	u64 expected_called_move_assigments		= 0,
	u64 expected_called_destructors			= 0
)
{
	std::string result = "";

	if (expected_called_def_constructors	!= called_def_constructors		) result += ">\tCalled def constructors is bad ("		+ std::to_string(called_def_constructors)		+ " != " + std::to_string(expected_called_def_constructors)		+ ");\n";
	if (expected_called_custom_constructors	!= called_custom_constructors	) result += ">\tCalled custom constructors is bad ("	+ std::to_string(called_custom_constructors)	+ " != " + std::to_string(expected_called_custom_constructors)	+ ");\n";
	if (expected_called_copy_constructors	!= called_copy_constructors		) result += ">\tCalled copy constructors is bad ("		+ std::to_string(called_copy_constructors)		+ " != " + std::to_string(expected_called_copy_constructors)	+ ");\n";
	if (expected_called_move_constructors	!= called_move_constructors		) result += ">\tCalled move constructors is bad ("		+ std::to_string(called_move_constructors)		+ " != " + std::to_string(expected_called_move_constructors)	+ ");\n";
	if (expected_called_copy_assigments		!= called_copy_assigments		) result += ">\tCalled copy assigments is bad ("		+ std::to_string(called_copy_assigments)		+ " != " + std::to_string(expected_called_copy_assigments)		+ ");\n";
	if (expected_called_move_assigments		!= called_move_assigments		) result += ">\tCalled move assigments is bad ("		+ std::to_string(called_move_assigments)		+ " != " + std::to_string(expected_called_move_assigments)		+ ");\n";
	if (expected_called_destructors			!= called_destructors			) result += ">\tCalled destructors is bad ("			+ std::to_string(called_destructors)			+ " != " + std::to_string(expected_called_destructors)			+ ");\n";

	if (result != "")
	{
		called_result = result;
		return false;
	}

	return true;
}

FLX_API_ bool test::test_self()
{
	output << "\nTesting self...\n";
	testee = "self";

	try
	{
		if (!noexcept(test_str()))													throw std::runtime_error("Def constructor is not noexcept.");
		if (!noexcept(test_str(15)))												throw std::runtime_error("Custom constructor is not noexcept.");
		if (!noexcept(test_str(test_str())))										throw std::runtime_error("Copy constructor is not noexcept.");
		if (!noexcept(test_str(std::move(test_str()))))								throw std::runtime_error("Move constructor is not noexcept.");
		if (!noexcept(std::declval<test_str&>() = std::declval<const test_str&>()))	throw std::runtime_error("Copy assignment is not noexcept.");
		if (!noexcept(std::declval<test_str&>() = std::declval<test_str&&>()))		throw std::runtime_error("Move assignment is not noexcept.");
		if (!noexcept(std::declval<test_str&>().~test_str()))						throw std::runtime_error("Destructor is not noexcept.");

		reset_calls_();
		if (!test_calls_()) throw std::runtime_error("Call counting is bad.");

		test_str a{};
		if (!test_calls_(1)) throw std::runtime_error("Def construction call counting is bad.");
		reset_calls_();

		test_str b{10};
		if (!test_calls_(0, 1)) throw std::runtime_error("Custom construction call counting is bad.");
		reset_calls_();

		test_str c{a};
		if (!test_calls_(0, 0, 1)) throw std::runtime_error("Copy construction call counting is bad.");
		reset_calls_();

		test_str d{std::move(a)};
		if (!test_calls_(0, 0, 0, 1)) throw std::runtime_error("Move construction call counting is bad.");
		reset_calls_();

		test_str e;
		reset_calls_();
		e = b;
		if (!test_calls_(0, 0, 0, 0, 1)) throw std::runtime_error("Copy assigment call counting is bad.");
		reset_calls_();

		test_str f = std::move(b);
		if (!test_calls_(0, 0, 0, 0, 0, 1)) throw std::runtime_error("Move assigment call counting is bad.");
		reset_calls_();

		{
			test_str g{};
			reset_calls_();
		}
		if (!test_calls_(0, 0, 0, 0, 0, 0, 1)) throw std::runtime_error("Move assigment call counting is bad.");
		reset_calls_();


		pass_();
		return true;
	}
	catch (std::exception e)
	{
		fail_(e.what());
		return false;
	}
}

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

	if (!test_self())
	{
		return false;
	}

	output << "\nFLX version is: " << FLX_VERSION << '\n';

	test_memory();
	test_dynamic_array();

	output << "\nFLX version is: " << FLX_VERSION << '\n';
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

bool test::test_memory()
{
	output << "\nTesting memory.hpp...\n";
	header = "memory.hpp";
	result_header = true;
	result_chunk = true;

	output << "+\tTesting functions (throwable skipped)...\n";
	chunk = "functions (throwable skipped)";
	{
		result_chunk = true;

		testee = "allocate(nothrow)";
		{
			try
			{
				if (!noexcept(allocate<test_str>(nothrow)))	throw std::runtime_error("Noexcept is bad.");

				std::array<test_str*, VOLUME> arr{};

				reset_calls_();

				for (u64 i = 0; i < VOLUME; i++)
				{
					arr[i] = allocate<test_str>(nothrow);
				}

				if (!test_calls_(VOLUME)) throw std::runtime_error("Calls are bad.");

				for (u64 i = 0; i < VOLUME; i++)
				{
					delete arr[i];
				}

				pass_();
			}
			catch (std::exception e)
			{
				fail_(e.what());
			}
		}

		testee = "allocate(nothrow, val_ty&&...)";
		{
			try
			{
				if (!noexcept(allocate<test_str>(nothrow, 10)))	throw std::runtime_error("Noexcept is bad.");

				std::array<test_str*, VOLUME> arr{};

				reset_calls_();

				for (u64 i = 0; i < VOLUME; i++)
				{
					arr[i] = allocate<test_str>(nothrow, 15ull);
				}

				for (u64 i = 0; i < VOLUME; i++)
				{
					if (arr[i]->data != 15ull) throw std::runtime_error("Data are bad.");
				}

				if (!test_calls_(0, VOLUME)) throw std::runtime_error("Calls are bad.");

				for (u64 i = 0; i < VOLUME; i++)
				{
					delete arr[i];
				}

				pass_();
			}
			catch (std::exception e)
			{
				fail_(e.what());
			}
		}

		testee = "deallocate(ty* const)";
		{
			try
			{
				if (!noexcept(deallocate<test_str>(nullptr)))	throw std::runtime_error("Noexcept is bad.");

				std::array<test_str*, VOLUME> arr{};
				for (u64 i = 0; i < VOLUME; i++)
				{
					arr[i] = new test_str{};
				}

				reset_calls_();

				for (u64 i = 0; i < VOLUME; i++)
				{
					deallocate(arr[i]);
				}

				if (!test_calls_(0, 0, 0, 0, 0, 0, VOLUME)) throw std::runtime_error("Calls are bad.");

				pass_();
			}
			catch (std::exception e)
			{
				fail_(e.what());
			}
		}

		testee = "allocate_array(const szt, nothrow)";
		{
			try
			{
				if (!noexcept(allocate_array<test_str>(VOLUME, nothrow)))	throw std::runtime_error("Noexcept is bad.");

				reset_calls_();

				test_str* a = allocate_array<test_str>(VOLUME, nothrow);

				if (!test_calls_(VOLUME)) throw std::runtime_error("Calls are bad.");

				delete[] a;

				pass_();
			}
			catch (std::exception e)
			{
				fail_(e.what());
			}
		}

		testee = "deallocate_array(ty* const)";
		{
			try
			{
				if (!noexcept(deallocate_array<void>(nullptr)))	throw std::runtime_error("Noexcept is bad.");

				test_str* a = new test_str[VOLUME];

				reset_calls_();

				deallocate_array(a);

				if (!test_calls_(0, 0, 0, 0, 0, 0, VOLUME)) throw std::runtime_error("Calls are bad.");

				pass_();
			}
			catch (std::exception e)
			{
				fail_(e.what());
			}
		}

		testee = "allocate_raw(const szt, nothrow)";
		{
			try
			{
				if (!noexcept(allocate_raw(VOLUME, nothrow)))	throw std::runtime_error("Noexcept is bad.");

				reset_calls_();

				test_str* a = static_cast<test_str*>(allocate_raw(VOLUME, nothrow));

				if (!test_calls_()) throw std::runtime_error("Calls are bad.");

				::operator delete(a);

				pass_();
			}
			catch (std::exception e)
			{
				fail_(e.what());
			}
		}

		testee = "deallocate_raw(void* const)";
		{
			try
			{
				if (!noexcept(deallocate_raw(nullptr)))	throw std::runtime_error("Noexcept is bad.");

				test_str* a = static_cast<test_str*>(::operator new(sizeof(test_str)));

				reset_calls_();

				deallocate_raw(a);

				if (!test_calls_()) throw std::runtime_error("Calls are bad.");

				pass_();
			}
			catch (std::exception e)
			{
				fail_(e.what());
			}
		}
	}
	chunk_status_();

	header_status_();

	return result_header;
}

bool test::test_dynamic_array()
{
	output << "\nTesting dynamic_array.hpp...\n";
	output << ".\tTesting dynamic_array...\n";
	bool result = true;
	constexpr u64 VOLUME = 1000;

	/*static u64 called_def_constructors = 0;
	static u64 called_custom_constructors = 0;
	static u64 called_copy_constructors = 0;
	static u64 called_move_constructors = 0;
	static u64 called_copy_assigments = 0;
	static u64 called_move_assigments = 0;
	static u64 called_destructors = 0;*/

	struct test_str
	{
		u64 data = 0xDEADDEADDEADDEAD;

		test_str() noexcept { data = 0xCCCCCCCCCCCCCCCC; called_def_constructors++; }
		test_str(const test_str& other) noexcept { data = other.data; called_copy_constructors++; }
		test_str(test_str&& other) noexcept { data = other.data; other.data = 0xCCCCCCCCCCCCCCCC; called_move_constructors++; }
		test_str& operator= (const test_str& other) noexcept { data = other.data; called_copy_assigments++; return *this; }
		test_str& operator= (test_str&& other) noexcept { data = other.data; other.data = 0xCCCCCCCCCCCCCCCC; called_move_assigments++; return *this; }
		~test_str() noexcept { data = 0xCCCCCCCCCCCCCCCC; called_destructors++; }
		test_str(u64 val) noexcept { called_custom_constructors++; data = val; }

		bool operator == (const test_str& other) const noexcept { return data == other.data; }
		bool operator != (const test_str& other) const noexcept { return data != other.data; }
	};

	// primitive types
	output << ".\t.\tTesting constructon with primitive types...\n";
	{
		// default constructor
		try
		{
			dynamic_array<i32> a{};
			dynamic_array<f32> b{};
			dynamic_array<b08> c{};
			dynamic_array<u64> d{};

			if (a.size_ != 0) throw std::runtime_error("Size is not null.");
			if (b.size_ != 0) throw std::runtime_error("Size is not null.");
			if (c.size_ != 0) throw std::runtime_error("Size is not null.");
			if (d.size_ != 0) throw std::runtime_error("Size is not null.");

			if (a.capacity_ != dynamic_array<i32>::PREALLOCATED_CAPACITY) throw std::runtime_error("Capacity is bad.");
			if (b.capacity_ != dynamic_array<f32>::PREALLOCATED_CAPACITY) throw std::runtime_error("Capacity is bad.");
			if (c.capacity_ != dynamic_array<b08>::PREALLOCATED_CAPACITY) throw std::runtime_error("Capacity is bad.");
			if (d.capacity_ != dynamic_array<u64>::PREALLOCATED_CAPACITY) throw std::runtime_error("Capacity is bad.");

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " Default constructor.\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " Default constructor: " << e.what() << '\n';
			result = false;
			tests_failed++;
		}

		// fill constructor
		try
		{
			dynamic_array<i32> a(VOLUME, 0);
			dynamic_array<f32> b(VOLUME, 0);
			dynamic_array<b08> c(VOLUME, 0);
			dynamic_array<u64> d(VOLUME, 0);

			if (a.data_ == nullptr) throw std::runtime_error("Data is null.");
			if (b.data_ == nullptr) throw std::runtime_error("Data is null.");
			if (c.data_ == nullptr) throw std::runtime_error("Data is null.");
			if (d.data_ == nullptr) throw std::runtime_error("Data is null.");

			if (a.size_ != VOLUME) throw std::runtime_error("Size is bad.");
			if (b.size_ != VOLUME) throw std::runtime_error("Size is bad.");
			if (c.size_ != VOLUME) throw std::runtime_error("Size is bad.");
			if (d.size_ != VOLUME) throw std::runtime_error("Size is bad.");

			if (a.capacity_ < VOLUME) throw std::runtime_error("Capacity is bad.");
			if (b.capacity_ < VOLUME) throw std::runtime_error("Capacity is bad.");
			if (c.capacity_ < VOLUME) throw std::runtime_error("Capacity is bad.");
			if (d.capacity_ < VOLUME) throw std::runtime_error("Capacity is bad.");

			i32* a_ptr = a.data_;
			f32* b_ptr = b.data_;
			b08* c_ptr = c.data_;
			u64* d_ptr = d.data_;

			for (u64 i = 0; i < VOLUME; i++)
			{
				if (a_ptr[i] != 0) throw std::runtime_error("Data is bad.");
				if (b_ptr[i] != 0) throw std::runtime_error("Data is bad.");
				if (c_ptr[i] != 0) throw std::runtime_error("Data is bad.");
				if (d_ptr[i] != 0) throw std::runtime_error("Data is bad.");
			}

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " Fill constructor.\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " Fill constructor: " << e.what() << '\n';
			result = false;
			tests_failed++;
		}

		// move constructor
		try
		{
			dynamic_array<i32> a(VOLUME, 0);
			dynamic_array<f32> b(VOLUME, 0);
			dynamic_array<b08> c(VOLUME, 0);
			dynamic_array<u64> d(VOLUME, 0);

			dynamic_array<i32> a1{ std::move(a) };
			dynamic_array<f32> b1{ std::move(b) };
			dynamic_array<b08> c1{ std::move(c) };
			dynamic_array<u64> d1{ std::move(d) };

			if (a.data_ != nullptr) throw std::runtime_error("Data is not null.");
			if (b.data_ != nullptr) throw std::runtime_error("Data is not null.");
			if (c.data_ != nullptr) throw std::runtime_error("Data is not null.");
			if (d.data_ != nullptr) throw std::runtime_error("Data is not null.");

			if (a.size_ != 0) throw std::runtime_error("Size is not null.");
			if (b.size_ != 0) throw std::runtime_error("Size is not null.");
			if (c.size_ != 0) throw std::runtime_error("Size is not null.");
			if (d.size_ != 0) throw std::runtime_error("Size is not null.");

			if (a.capacity_ != 0) throw std::runtime_error("Capacity is not null.");
			if (b.capacity_ != 0) throw std::runtime_error("Capacity is not null.");
			if (c.capacity_ != 0) throw std::runtime_error("Capacity is not null.");
			if (d.capacity_ != 0) throw std::runtime_error("Capacity is not null.");

			if (a1.data_ == nullptr) throw std::runtime_error("Data is null.");
			if (b1.data_ == nullptr) throw std::runtime_error("Data is null.");
			if (c1.data_ == nullptr) throw std::runtime_error("Data is null.");
			if (d1.data_ == nullptr) throw std::runtime_error("Data is null.");

			if (a1.size_ != VOLUME) throw std::runtime_error("Size is bad.");
			if (b1.size_ != VOLUME) throw std::runtime_error("Size is bad.");
			if (c1.size_ != VOLUME) throw std::runtime_error("Size is bad.");
			if (d1.size_ != VOLUME) throw std::runtime_error("Size is bad.");

			if (a1.capacity_ < VOLUME) throw std::runtime_error("Capacity is bad.");
			if (b1.capacity_ < VOLUME) throw std::runtime_error("Capacity is bad.");
			if (c1.capacity_ < VOLUME) throw std::runtime_error("Capacity is bad.");
			if (d1.capacity_ < VOLUME) throw std::runtime_error("Capacity is bad.");

			for (u64 i = 0; i < VOLUME; i++)
			{
				if (a1.data_[i] != 0) throw std::runtime_error("Data is bad.");
				if (b1.data_[i] != 0) throw std::runtime_error("Data is bad.");
				if (c1.data_[i] != 0) throw std::runtime_error("Data is bad.");
				if (d1.data_[i] != 0) throw std::runtime_error("Data is bad.");
			}

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " Move constructor.\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " Move constructor: " << e.what() << '\n';
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

			if (a.data_ == a1.data_) throw std::runtime_error("Data is same.");
			if (b.data_ == b1.data_) throw std::runtime_error("Data is same.");
			if (c.data_ == c1.data_) throw std::runtime_error("Data is same.");
			if (d.data_ == d1.data_) throw std::runtime_error("Data is same.");

			if (a.size_ != a1.size_) throw std::runtime_error("Size is bad.");
			if (b.size_ != b1.size_) throw std::runtime_error("Size is bad.");
			if (c.size_ != c1.size_) throw std::runtime_error("Size is bad.");
			if (d.size_ != d1.size_) throw std::runtime_error("Size is bad.");

			if (a.capacity_ != a1.capacity_) throw std::runtime_error("Capacity is bad.");
			if (b.capacity_ != b1.capacity_) throw std::runtime_error("Capacity is bad.");
			if (c.capacity_ != c1.capacity_) throw std::runtime_error("Capacity is bad.");
			if (d.capacity_ != d1.capacity_) throw std::runtime_error("Capacity is bad.");

			dynamic_array<i32> a2(VOLUME, 0);
			dynamic_array<f32> b2(VOLUME, 0);
			dynamic_array<b08> c2(VOLUME, 0);
			dynamic_array<u64> d2(VOLUME, 0);

			dynamic_array<i32> a12{ a2 };
			dynamic_array<f32> b12{ b2 };
			dynamic_array<b08> c12{ c2 };
			dynamic_array<u64> d12{ d2 };

			if (a2.data_ == a12.data_) throw std::runtime_error("Data is same.");
			if (b2.data_ == b12.data_) throw std::runtime_error("Data is same.");
			if (c2.data_ == c12.data_) throw std::runtime_error("Data is same.");
			if (d2.data_ == d12.data_) throw std::runtime_error("Data is same.");

			if (a2.size_ != a12.size_) throw std::runtime_error("Size is bad.");
			if (b2.size_ != b12.size_) throw std::runtime_error("Size is bad.");
			if (c2.size_ != c12.size_) throw std::runtime_error("Size is bad.");
			if (d2.size_ != d12.size_) throw std::runtime_error("Size is bad.");

			if (a2.capacity_ != a12.capacity_) throw std::runtime_error("Capacity is bad.");
			if (b2.capacity_ != b12.capacity_) throw std::runtime_error("Capacity is bad.");
			if (c2.capacity_ != c12.capacity_) throw std::runtime_error("Capacity is bad.");
			if (d2.capacity_ != d12.capacity_) throw std::runtime_error("Capacity is bad.");

			for (u64 i = 0; i < VOLUME; i++)
			{
				if (a2.data_[i] != a12.data_[i]) throw std::runtime_error("Data is bad.");
				if (b2.data_[i] != b12.data_[i]) throw std::runtime_error("Data is bad.");
				if (c2.data_[i] != c12.data_[i]) throw std::runtime_error("Data is bad.");
				if (d2.data_[i] != d12.data_[i]) throw std::runtime_error("Data is bad.");
			}

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " Copy constructor.\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " Copy constructor: " << e.what() << '\n';
			result = false;
			tests_failed++;
		}

		// operator =
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

			if (a.data_ == a1.data_) throw std::runtime_error("Data is same.");
			if (b.data_ == b1.data_) throw std::runtime_error("Data is same.");
			if (c.data_ == c1.data_) throw std::runtime_error("Data is same.");
			if (d.data_ == d1.data_) throw std::runtime_error("Data is same.");

			if (a.size_ != a1.size_) throw std::runtime_error("Size is bad.");
			if (b.size_ != b1.size_) throw std::runtime_error("Size is bad.");
			if (c.size_ != c1.size_) throw std::runtime_error("Size is bad.");
			if (d.size_ != d1.size_) throw std::runtime_error("Size is bad.");

			if (a.capacity_ != a1.capacity_) throw std::runtime_error("Capacity is bad.");
			if (b.capacity_ != b1.capacity_) throw std::runtime_error("Capacity is bad.");
			if (c.capacity_ != c1.capacity_) throw std::runtime_error("Capacity is bad.");
			if (d.capacity_ != d1.capacity_) throw std::runtime_error("Capacity is bad.");

			dynamic_array<i32> a2(VOLUME, 0);
			dynamic_array<f32> b2(VOLUME, 0);
			dynamic_array<b08> c2(VOLUME, 0);
			dynamic_array<u64> d2(VOLUME, 0);

			dynamic_array<i32> a12{ a2 };
			dynamic_array<f32> b12{ b2 };
			dynamic_array<b08> c12{ c2 };
			dynamic_array<u64> d12{ d2 };

			if (a2.data_ == a12.data_) throw std::runtime_error("Data is same.");
			if (b2.data_ == b12.data_) throw std::runtime_error("Data is same.");
			if (c2.data_ == c12.data_) throw std::runtime_error("Data is same.");
			if (d2.data_ == d12.data_) throw std::runtime_error("Data is same.");

			if (a2.size_ != a12.size_) throw std::runtime_error("Size is bad.");
			if (b2.size_ != b12.size_) throw std::runtime_error("Size is bad.");
			if (c2.size_ != c12.size_) throw std::runtime_error("Size is bad.");
			if (d2.size_ != d12.size_) throw std::runtime_error("Size is bad.");

			if (a2.capacity_ != a12.capacity_) throw std::runtime_error("Capacity is bad.");
			if (b2.capacity_ != b12.capacity_) throw std::runtime_error("Capacity is bad.");
			if (c2.capacity_ != c12.capacity_) throw std::runtime_error("Capacity is bad.");
			if (d2.capacity_ != d12.capacity_) throw std::runtime_error("Capacity is bad.");

			for (u64 i = 0; i < VOLUME; i++)
			{
				if (a2.data_[i] != a12.data_[i]) throw std::runtime_error("Data is bad.");
				if (b2.data_[i] != b12.data_[i]) throw std::runtime_error("Data is bad.");
				if (c2.data_[i] != c12.data_[i]) throw std::runtime_error("Data is bad.");
				if (d2.data_[i] != d12.data_[i]) throw std::runtime_error("Data is bad.");
			}

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " Copy assignment.\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " Copy assignment: " << e.what() << '\n';
			result = false;
			tests_failed++;
		}
	}
	output << ".\t.\t.\t.\t\n";

	// non-trivial types
	output << ".\t.\tTesting construction with non-primitive types...\n";

	//TODO: add checks for all calls
	// 
	// counting VOLUME of constructor calls
	{
		// fill constructor()
		try
		{
			called_copy_constructors = 0;

			dynamic_array<test_str> a(VOLUME, 0);

			if (called_copy_constructors != VOLUME) throw std::runtime_error("Amount of construction calls is bad.");

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " Fill constructor - calls.\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " Fill constructor - calls: " << e.what() << '\n';
			result = false;
			tests_failed++;
		}
	}

	// no default constructor
	{
		output << ".\t.\t.\tTesting construction with no-default-constructor type...\n";

		struct no_default
		{
			i32 data_ = 10;

			no_default() noexcept = delete;
			no_default(i32 a) noexcept { data_ = a; };
			no_default(const no_default&) noexcept = default;
			no_default(no_default&&) noexcept = default;
		};

		// default constructor
		try
		{
			dynamic_array<no_default> a{};

			if (a.size_ != 0) throw std::runtime_error("Size is not null.");

			if (a.capacity_ != dynamic_array<no_default>::PREALLOCATED_CAPACITY) throw std::runtime_error("Capacity is bad.");

			output << ".\t.\t.\t.\t" << GREEN << "PASSED" << RESET << " Default constructor.\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t.\t" << RED << "FAILED" << RESET << " Default constructor: " << e.what() << '\n';
			result = false;
			tests_failed++;
		}

		// fill constructor
		try
		{
			dynamic_array<no_default> a(VOLUME, 0);

			if (a.data_ == nullptr) throw std::runtime_error("Data is null.");

			if (a.size_ != VOLUME) throw std::runtime_error("Size is bad.");

			if (a.capacity_ < VOLUME) throw std::runtime_error("Capacity is bad.");

			no_default* a_ptr = a.data_;

			for (u64 i = 0; i < VOLUME; i++)
			{
				if (a_ptr[i].data_ != 0) throw std::runtime_error("Data is bad.");
			}

			output << ".\t.\t.\t.\t" << GREEN << "PASSED" << RESET << " Fill constructor.\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t.\t" << RED << "FAILED" << RESET << " Fill constructor: " << e.what() << '\n';
			result = false;
			tests_failed++;
		}

		// move constructor
		try
		{
			dynamic_array<no_default> a(VOLUME, 0);

			dynamic_array<no_default> a1{ std::move(a) };

			if (a.data_ != nullptr) throw std::runtime_error("Data is not null.");

			if (a.size_ != 0) throw std::runtime_error("Size is not null.");

			if (a.capacity_ != 0) throw std::runtime_error("Capacity is not null.");

			if (a1.data_ == nullptr) throw std::runtime_error("Data is null.");

			if (a1.size_ != VOLUME) throw std::runtime_error("Size is bad.");

			if (a1.capacity_ < VOLUME) throw std::runtime_error("Capacity is bad.");

			for (u64 i = 0; i < VOLUME; i++)
			{
				if (a1.data_[i].data_ != 0) throw std::runtime_error("Data is bad.");
			}

			output << ".\t.\t.\t.\t" << GREEN << "PASSED" << RESET << " Move constructor.\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t.\t" << RED << "FAILED" << RESET << " Move constructor: " << e.what() << '\n';
			result = false;
			tests_failed++;
		}

		// copy constructor
		try
		{
			dynamic_array<no_default> a{};

			dynamic_array<no_default> a1{ a };

			if (a.data_ == a1.data_) throw std::runtime_error("Data is same.");

			if (a.size_ != a1.size_) throw std::runtime_error("Size is bad.");

			if (a.capacity_ != a1.capacity_) throw std::runtime_error("Capacity is bad.");

			dynamic_array<no_default> a2(VOLUME, 0);

			dynamic_array<no_default> a12{ a2 };

			if (a2.data_ == a12.data_) throw std::runtime_error("Data is same.");

			if (a2.size_ != a12.size_) throw std::runtime_error("Size is bad.");

			if (a2.capacity_ != a12.capacity_) throw std::runtime_error("Capacity is bad.");

			for (u64 i = 0; i < VOLUME; i++)
			{
				if (a2.data_[i].data_ != a12.data_[i].data_) throw std::runtime_error("Data is bad.");
			}

			output << ".\t.\t.\t.\t" << GREEN << "PASSED" << RESET << " Copy constructor.\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t.\t" << RED << "FAILED" << RESET << " Copy constructor: " << e.what() << '\n';
			result = false;
			tests_failed++;
		}

		// operator =
		try
		{
			dynamic_array<no_default> a{};

			dynamic_array<no_default> a1{ a };

			if (a.data_ == a1.data_) throw std::runtime_error("Data is same.");

			if (a.size_ != a1.size_) throw std::runtime_error("Size is bad.");

			if (a.capacity_ != a1.capacity_) throw std::runtime_error("Capacity is bad.");

			dynamic_array<no_default> a2(VOLUME, 0);

			dynamic_array<no_default> a12{ a2 };

			if (a2.data_ == a12.data_) throw std::runtime_error("Data is same.");

			if (a2.size_ != a12.size_) throw std::runtime_error("Size is bad.");

			if (a2.capacity_ != a12.capacity_) throw std::runtime_error("Capacity is bad.");

			for (u64 i = 0; i < VOLUME; i++)
			{
				if (a2.data_[i].data_ != a12.data_[i].data_) throw std::runtime_error("Data is bad.");
			}

			output << ".\t.\t.\t.\t" << GREEN << "PASSED" << RESET << " Copy assigment.\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t.\t" << RED << "FAILED" << RESET << " Copy assigment: " << e.what() << '\n';
			result = false;
			tests_failed++;
		}
	}

	{} // no copy constructor // these braces allows VS to see braces below
	{
		output << ".\t.\t.\tTesting construction with no-copy-constructor type...\n";

		struct no_copy
		{
			i32 data_ = 0;

			no_copy() noexcept {};
			no_copy(i32 a) noexcept { data_ = a; };
			no_copy(const no_copy&) noexcept = delete;
			no_copy(no_copy&&) noexcept = default;
		};

		// default constructor
		try
		{
			dynamic_array<no_copy> a{};

			if (a.size_ != 0) throw std::runtime_error("Size is not null.");

			if (a.capacity_ != dynamic_array<no_copy>::PREALLOCATED_CAPACITY) throw std::runtime_error("Capacity is bad.");

			output << ".\t.\t.\t.\t" << GREEN << "PASSED" << RESET << " Default constructor.\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t.\t" << RED << "FAILED" << RESET << " Default constructor: " << e.what() << '\n';
			result = false;
			tests_failed++;
		}

		// move constructor
		try
		{
			dynamic_array<no_copy> a;

			dynamic_array<no_copy> a1{ std::move(a) };

			if (a.data_ != nullptr) throw std::runtime_error("Data is not null.");

			if (a1.data_ == nullptr) throw std::runtime_error("Data is null.");

			output << ".\t.\t.\t.\t" << GREEN << "PASSED" << RESET << " Move constructor.\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t.\t" << RED << "FAILED" << RESET << " Move constructor: " << e.what() << '\n';
			result = false;
			tests_failed++;
		}
	}
	output << ".\t.\t.\t.\t.\t\n";

	// destruction
	output << ".\t.\tTesting destruction...\n";
	{
		try
		{

			i32* a_ptr;
			test_str* b_ptr;

			{
				dynamic_array<i32> a(VOLUME, 0);
				dynamic_array<test_str> b(VOLUME, 0);

				a_ptr = a.data_;
				b_ptr = b.data_;

				called_destructors = 0;
			}

			if (called_destructors != VOLUME) throw std::runtime_error("Amount of destruction calls is bad.");

			/*try
			{
				*a_ptr = 0;
				*b_ptr = 0;

				throw std::runtime_error("Data is not freed.");
			}
			catch (std::runtime_error e)
			{
				throw std::runtime_error("Data is not freed.");
			}
			catch (...)
			{
				output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " Destructor.\n";
				tests_passed++;
			}*/

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " Destructor.\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " Destructor: " << e.what() << '\n';
			result = false;
			tests_failed++;
		}
	}
	output << ".\t.\t.\t.\t\n";

	// common operations
	output << ".\t.\tTesting basic operations...\n";
	{
		dynamic_array<i32> a(VOLUME, 0);
		dynamic_array<test_str> b(VOLUME, 0);

		// data()
		try
		{
			if (a.data() != a.data_) throw std::runtime_error("Data is not data_.");
			if (b.data() != b.data_) throw std::runtime_error("Data is not data_.");

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " data().\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " data(): " << e.what() << '\n';
			result = false;
			tests_failed++;
		}
		
		// empty()
		try
		{
			dynamic_array<i32> a1(VOLUME, 0);
			dynamic_array<test_str> b1(VOLUME, 0);
			dynamic_array<i32> a2;
			dynamic_array<test_str> b2;

			a1.clear();
			b1.clear();

			if (!a1.empty()) throw std::runtime_error("Bad.");
			if (!b1.empty()) throw std::runtime_error("Bad.");
			if (!a2.empty()) throw std::runtime_error("Bad.");
			if (!b2.empty()) throw std::runtime_error("Bad.");

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " empty().\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " empty(): " << e.what() << '\n';
			result = false;
			tests_failed++;
		}

		// max_size()
		try
		{
			dynamic_array<i32, u64> a1;
			dynamic_array<i32, u32> a2;
			dynamic_array<i32, u08> a3;

			dynamic_array<test_str, u64> b1;
			dynamic_array<test_str, u32> b2;
			dynamic_array<test_str, u08> b3;

			if (a1.max_size() != std::numeric_limits<u64>::max()) throw std::runtime_error("Bad.");
			if (a2.max_size() != std::numeric_limits<u32>::max()) throw std::runtime_error("Bad.");
			if (a3.max_size() != std::numeric_limits<u08>::max()) throw std::runtime_error("Bad.");

			if (b1.max_size() != std::numeric_limits<u64>::max()) throw std::runtime_error("Bad.");
			if (b2.max_size() != std::numeric_limits<u32>::max()) throw std::runtime_error("Bad.");
			if (b3.max_size() != std::numeric_limits<u08>::max()) throw std::runtime_error("Bad.");

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " max_size().\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " max_size(): " << e.what() << '\n';
			result = false;
			tests_failed++;
		}

		// size()
		try
		{
			if (a.size() != VOLUME) throw std::runtime_error("Bad.");
			if (b.size() != VOLUME) throw std::runtime_error("Bad.");

			if (a.size() != a.size_) throw std::runtime_error("Bad.");
			if (b.size() != b.size_) throw std::runtime_error("Bad.");

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " size().\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " size(): " << e.what() << '\n';
			result = false;
			tests_failed++;
		}

		// capacity()
		try
		{
			if (a.capacity() != a.capacity_) throw std::runtime_error("Bad.");
			if (b.capacity() != b.capacity_) throw std::runtime_error("Bad.");

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " capacity().\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " capacity(): " << e.what() << '\n';
			result = false;
			tests_failed++;
		}
	}
	output << ".\t.\t.\t.\t\n";

	// iterators
	output << ".\t.\tTesting iterators...\n";
	{
		dynamic_array<i32> a(VOLUME, 0);
		dynamic_array<test_str> b(VOLUME, 0);

		// begin()
		try
		{
			if (a.begin().ptr != &a.data_[0]) throw std::runtime_error("Ptr addr is bad.");
			if (b.begin().ptr != &b.data_[0]) throw std::runtime_error("Ptr addr is bad.");

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " begin().\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " begin(): " << e.what() << '\n';
			result = false;
			tests_failed++;
		}

		// end()
		try
		{
			if (a.end().ptr != &a.data_[VOLUME]) throw std::runtime_error("Ptr addr is bad.");
			if (b.end().ptr != &b.data_[VOLUME]) throw std::runtime_error("Ptr addr is bad.");

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " end().\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " end(): " << e.what() << '\n';
			result = false;
			tests_failed++;
		}

		// cbegin()
		try
		{
			if (a.cbegin().ptr != &a.data_[0]) throw std::runtime_error("Ptr addr is bad.");
			if (b.cbegin().ptr != &b.data_[0]) throw std::runtime_error("Ptr addr is bad.");

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " cbegin().\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " cbegin(): " << e.what() << '\n';
			result = false;
			tests_failed++;
		}

		// end()
		try
		{
			if (a.cend().ptr != &a.data_[VOLUME]) throw std::runtime_error("Ptr addr is bad.");
			if (b.cend().ptr != &b.data_[VOLUME]) throw std::runtime_error("Ptr addr is bad.");

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " cend().\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " cend(): " << e.what() << '\n';
			result = false;
			tests_failed++;
		}
	}
	output << ".\t.\t.\t.\t\n";

	// modifiers
	output << ".\t.\tTesting modifiers...\n";
	{
		// clear()
		try
		{
			dynamic_array<i32> a1(VOLUME, 0);
			dynamic_array<test_str> b1(VOLUME, 0);

			called_destructors = 0;
			a1.clear();
			b1.clear();

			if (called_destructors != VOLUME) throw std::runtime_error("Amount of destruction calls is bad.");

			if (a1.data_ == nullptr) throw std::runtime_error("Data is null.");
			if (b1.data_ == nullptr) throw std::runtime_error("Data is null.");

			if (a1.size_ != 0) throw std::runtime_error("Size is not null.");
			if (b1.size_ != 0) throw std::runtime_error("Size is not null.");

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " clear().\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " clear(): " << e.what() << '\n';
			result = false;
			tests_failed++;
		}

		// push_back(const ty&)
		try
		{
			test_str val{};
			{
				called_def_constructors = 0;
				called_custom_constructors = 0;
				called_copy_constructors = 0;
				called_move_constructors = 0;
				called_copy_assigments = 0;
				called_move_assigments = 0;
				called_destructors = 0;

				dynamic_array<test_str> a{};
				
				for (u64 i = 0; i < VOLUME; i++)
				{
					a.push_back(val);
				}


				if (a.size_ != VOLUME) throw std::runtime_error("Size is bad.");

				for (u64 i = 0; i < VOLUME; i++)
				{
					if (a.data_[i] != val) throw std::runtime_error("Data is bad.");
				}
			}

			if (called_def_constructors != 0)		throw std::runtime_error("Called def constructors is not null.");
			if (called_custom_constructors != 0)	throw std::runtime_error("Called custom constructors is not null.");
			if (called_copy_constructors != VOLUME)	throw std::runtime_error("Called copy constructors is bad.");
			//if (called_move_constructors != 0)	throw std::runtime_error("Called move constructors is not null."); // they are called when reallocating
			if (called_copy_assigments != 0)			throw std::runtime_error("Called copy assigments is not null.");
			if (called_move_assigments != 0)			throw std::runtime_error("Called move assigments is not null.");
			if (called_destructors != called_move_constructors + called_copy_constructors) throw std::runtime_error("Called destructors is bad."); // should match moves + copies

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " push_back(const ty&).\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " push_back(const ty&): " << e.what() << '\n';
			result = false;
			tests_failed++;
		}

		// push_back(ty&&)
		try
		{
			test_str val[VOLUME];
			for (u64 i = 0; i < VOLUME; i++)
			{
				val[i] = i;
			}
			{
				called_def_constructors = 0;
				called_custom_constructors = 0;
				called_copy_constructors = 0;
				called_move_constructors = 0;
				called_copy_assigments = 0;
				called_move_assigments = 0;
				called_destructors = 0;

				dynamic_array<test_str> a{};

				for (u64 i = 0; i < VOLUME; i++)
				{
					a.push_back(std::move(val[i]));
				}

				if (a.size_ != VOLUME) throw std::runtime_error("Size is bad.");

				for (u64 i = 0; i < VOLUME; i++)
				{
					if (a.data_[i].data != i) throw std::runtime_error("Data is bad.");
				}
			}

			if (called_def_constructors != 0)		throw std::runtime_error("Called def constructors is not null.");
			if (called_custom_constructors != 0)	throw std::runtime_error("Called custom constructors is not null.");
			if (called_copy_constructors != 0)		throw std::runtime_error("Called copy constructors is not null.");
			//if (called_move_constructors != 0) throw std::runtime_error("Called move constructors is not null."); // they are called when reallocating
			if (called_copy_assigments != 0)			throw std::runtime_error("Called copy assigments is not null.");
			if (called_move_assigments != 0)			throw std::runtime_error("Called move assigments is not null.");
			if (called_destructors != called_move_constructors + called_copy_constructors) throw std::runtime_error("Called destructors is bad."); // should match moves + copies

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " push_back(ty&&).\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " push_back(ty&&): " << e.what() << '\n';
			result = false;
			tests_failed++;
		}

		// emplace_back(val_ty&&...)
		try
		{
			{
				called_def_constructors = 0;
				called_custom_constructors = 0;
				called_copy_constructors = 0;
				called_move_constructors = 0;
				called_copy_assigments = 0;
				called_move_assigments = 0;
				called_destructors = 0;

				dynamic_array<test_str> a{};

				for (u64 i = 0; i < VOLUME; i++)
				{
					a.emplace_back(i);
				}

				if (a.size_ != VOLUME) throw std::runtime_error("Size is bad.");

				for (u64 i = 0; i < VOLUME; i++)
				{
					if (a.data_[i].data != i) throw std::runtime_error("Data is bad.");
				}
			}

			if (called_def_constructors != 0)			throw std::runtime_error("Called def constructors is not null.");
			if (called_custom_constructors != VOLUME)	throw std::runtime_error("Called custom constructors is bad.");
			if (called_copy_constructors != 0)			throw std::runtime_error("Called copy constructors is not null.");
			//if (called_move_constructors != 0) throw std::runtime_error("Called move constructors is not null."); // they are called when reallocating
			if (called_copy_assigments != 0)				throw std::runtime_error("Called copy assigments is not null.");
			if (called_move_assigments != 0)				throw std::runtime_error("Called move assigments is not null.");
			if (called_destructors != called_move_constructors + called_custom_constructors) throw std::runtime_error("Called destructors is bad."); // should match moves + copies + custom constructors

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " emplace_back(val_ty&&...).\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " emplace_back(val_ty&&...): " << e.what() << '\n';
			result = false;
			tests_failed++;
		}

		// pop_back()
		try
		{
			dynamic_array<test_str> a(VOLUME, 0);
			{
				called_def_constructors = 0;
				called_custom_constructors = 0;
				called_copy_constructors = 0;
				called_move_constructors = 0;
				called_copy_assigments = 0;
				called_move_assigments = 0;
				called_destructors = 0;

				for (u64 i = 0; i < VOLUME; i++)
				{
					a.pop_back();
				}

				if (a.size_ != 0) throw std::runtime_error("Size is bad.");
			}

			if (called_def_constructors != 0)		throw std::runtime_error("Called def constructors is not null.");
			if (called_custom_constructors != 0)	throw std::runtime_error("Called custom constructors is not null.");
			if (called_copy_constructors != 0)		throw std::runtime_error("Called copy constructors is not null.");
			if (called_move_constructors != 0)		throw std::runtime_error("Called move constructors is not null."); // they are called when reallocating
			if (called_copy_assigments != 0)			throw std::runtime_error("Called copy assigments is not null.");
			if (called_move_assigments != 0)			throw std::runtime_error("Called move assigments is not null.");
			if (called_destructors != VOLUME)		throw std::runtime_error("Called destructors is bad."); // should match moves + copies + custom constructors

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " pop_back().\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " pop_back(): " << e.what() << '\n';
			result = false;
			tests_failed++;
		}

		// erase(iter)
		try
		{
			dynamic_array<test_str> a(VOLUME, 0);
			{
				called_def_constructors = 0;
				called_custom_constructors = 0;
				called_copy_constructors = 0;
				called_move_constructors = 0;
				called_copy_assigments = 0;
				called_move_assigments = 0;
				called_destructors = 0;

				for (u64 i = 0; i < VOLUME; i++)
				{
					a.erase(a.begin() + rand() % a.size_);
				}

				if (a.size_ != 0) throw std::runtime_error("Size is bad.");
			}

			if (called_def_constructors != 0)		throw std::runtime_error("Called def constructors is not null.");
			if (called_custom_constructors != 0)	throw std::runtime_error("Called custom constructors is not null.");
			if (called_copy_constructors != 0)		throw std::runtime_error("Called copy constructors is not null.");
			//if (called_move_constructors != 0)		throw std::runtime_error("Called move constructors is not null."); // they are called when reallocating
			if (called_copy_assigments != 0)			throw std::runtime_error("Called copy assigments is not null.");
			if (called_move_assigments != 0)			throw std::runtime_error("Called move assigments is not null.");
			if (called_destructors != VOLUME)		throw std::runtime_error("Called destructors is bad."); // should match moves + copies + custom constructors

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " erase(iter).\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " erase(iter): " << e.what() << '\n';
			result = false;
			tests_failed++;
		}

		// erase(iter, iter)
		try
		{
			dynamic_array<test_str> a(10, 0);
			for (u64 i = 0; i < 10; i++)
			{
				a.data_[i] = i;
			}
			{
				called_def_constructors = 0;
				called_custom_constructors = 0;
				called_copy_constructors = 0;
				called_move_constructors = 0;
				called_copy_assigments = 0;
				called_move_assigments = 0;
				called_destructors = 0;

				a.erase(a.begin() + 2, a.end() - 2); // [ 2, 8 ), killing 6

				if (a.size_ != 4) throw std::runtime_error("Size is bad.");

				if (a.data_[0].data != 0)	throw std::runtime_error("Data is bad.");
				if (a.data_[1].data != 1)	throw std::runtime_error("Data is bad.");
				if (a.data_[2].data != 8)	throw std::runtime_error("Data is bad.");
				if (a.data_[3].data != 9)	throw std::runtime_error("Data is bad.");

				a.erase(a.begin() + 1, a.end() - 1); // [ 1, 3 ), killing 2

				if (a.size_ != 2) throw std::runtime_error("Size is bad.");

				if (a.data_[0].data != 0)	throw std::runtime_error("Data is bad.");
				if (a.data_[1].data != 9)	throw std::runtime_error("Data is bad.");

				a.erase(a.begin(), a.end()); // [ 0, 2 ), killing 2

				if (a.size_ != 0) throw std::runtime_error("Size is bad.");
			}

			if (called_def_constructors != 0)		throw std::runtime_error("Called def constructors is not null.");
			if (called_custom_constructors != 0)	throw std::runtime_error("Called custom constructors is not null.");
			if (called_copy_constructors != 0)		throw std::runtime_error("Called copy constructors is not null.");
			//if (called_move_constructors != 0)		throw std::runtime_error("Called move constructors is not null."); // they are called when reallocating
			if (called_copy_assigments != 0)			throw std::runtime_error("Called copy assigments is not null.");
			if (called_move_assigments != 0)			throw std::runtime_error("Called move assigments is not null.");
			if (called_destructors != 10)			throw std::runtime_error("Called destructors is bad."); // should match moves + copies + custom constructors

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " erase(iter, iter).\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " erase(iter, iter): " << e.what() << '\n';
			result = false;
			tests_failed++;
		}
	}
	output << ".\t.\t.\t.\t\n";

	// element access
	output << ".\t.\tTesting element access...\n";
	{
		// operator[] (size_ty)
		
		try
		{
			dynamic_array<test_str, u64> a(VOLUME, 0);
			for (u64 i = 0; i < VOLUME; i++)
			{
				a.data_[i].data = i;
			}

			{
				called_def_constructors = 0;
				called_custom_constructors = 0;
				called_copy_constructors = 0;
				called_move_constructors = 0;
				called_copy_assigments = 0;
				called_move_assigments = 0;
				called_destructors = 0;

				for (u64 i = 0; i < VOLUME; i++)
				{
					if (a[i].data != i) throw std::runtime_error("Bad.");
				}

				if (called_def_constructors != 0)		throw std::runtime_error("Called def constructors is not null.");
				if (called_custom_constructors != 0)	throw std::runtime_error("Called custom constructors is not null.");
				if (called_copy_constructors != 0)		throw std::runtime_error("Called copy constructors is not null.");
				if (called_move_constructors != 0)		throw std::runtime_error("Called move constructors is not null."); // they are called when reallocating
				if (called_copy_assigments != 0)			throw std::runtime_error("Called copy assigments is not null.");
				if (called_move_assigments != 0)			throw std::runtime_error("Called move assigments is not null.");
				if (called_destructors != 0)			throw std::runtime_error("Called destructors is not null."); // should match moves + copies
			}

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " operator[] (size_ty).\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " operator[] (size_ty): " << e.what() << '\n';
			result = false;
			tests_failed++;
		}
		
	}
	output << ".\t.\t.\t.\t\n";

	output << (result ? ".\tdynamic_array " GREEN "PASSED" RESET ".\n" : "dynamic_array " RED "FAILED" RESET ".\n");

	output << ".\t.\t\n";

	output << (result ? "dynamic_array.hpp " GREEN "PASSED" RESET ".\n\n" : "dynamic_array.hpp " RED "FAILED" RESET ".\n\n");

	return result;
}
