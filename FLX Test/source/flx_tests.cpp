#include "flx_tests.hpp"

#include "flx/imp_core.hpp"
#include "flx/new.hpp"
#include "flx/type_traits.hpp"
#include "flx/concepts.hpp"
#include "flx/utility.hpp"
#include "flx/dynamic_array.hpp"

#include <sstream>
#include <exception>

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"

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
	output << ".\t.\t\n";
	output << (result ? "dynamic_array " GREEN "PASSED" RESET ".\n\n" : "dynamic_array " RED "FAILED" RESET ".\n\n");

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
	constexpr u64 amount = 10;

	output << ".\tTesting constructon with primitive types...\n";

	// primitive types
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

			output << ".\t.\t" << GREEN << "PASSED" << RESET << " Default constructor.\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t" << RED << "FAILED" << RESET << " Default constructor: " << e.what() << '\n';
			result = false;
			tests_failed++;
		}

		// fill constructor
		try
		{
			dynamic_array<i32> a(amount, 0);
			dynamic_array<f32> b(amount, 0);
			dynamic_array<b08> c(amount, 0);
			dynamic_array<u64> d(amount, 0);

			if (a.data_ == nullptr) throw std::runtime_error("Data is null.");
			if (b.data_ == nullptr) throw std::runtime_error("Data is null.");
			if (c.data_ == nullptr) throw std::runtime_error("Data is null.");
			if (d.data_ == nullptr) throw std::runtime_error("Data is null.");

			if (a.size_ != amount) throw std::runtime_error("Size is bad.");
			if (b.size_ != amount) throw std::runtime_error("Size is bad.");
			if (c.size_ != amount) throw std::runtime_error("Size is bad.");
			if (d.size_ != amount) throw std::runtime_error("Size is bad.");

			if (a.capacity_ < amount) throw std::runtime_error("Capacity is bad.");
			if (b.capacity_ < amount) throw std::runtime_error("Capacity is bad.");
			if (c.capacity_ < amount) throw std::runtime_error("Capacity is bad.");
			if (d.capacity_ < amount) throw std::runtime_error("Capacity is bad.");

			i32* a_ptr = a.data_;
			f32* b_ptr = b.data_;
			b08* c_ptr = c.data_;
			u64* d_ptr = d.data_;

			for (u64 i = 0; i < amount; i++)
			{
				if (a_ptr[i] != 0) throw std::runtime_error("Data is bad.");
				if (b_ptr[i] != 0) throw std::runtime_error("Data is bad.");
				if (c_ptr[i] != 0) throw std::runtime_error("Data is bad.");
				if (d_ptr[i] != 0) throw std::runtime_error("Data is bad.");
			}

			output << ".\t.\t" << GREEN << "PASSED" << RESET << " Fill constructor.\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t" << RED << "FAILED" << RESET << " Fill constructor: " << e.what() << '\n';
			result = false;
			tests_failed++;
		}

		// move constructor
		try
		{
			dynamic_array<i32> a(amount, 0);
			dynamic_array<f32> b(amount, 0);
			dynamic_array<b08> c(amount, 0);
			dynamic_array<u64> d(amount, 0);

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

			if (a1.size_ != amount) throw std::runtime_error("Size is bad.");
			if (b1.size_ != amount) throw std::runtime_error("Size is bad.");
			if (c1.size_ != amount) throw std::runtime_error("Size is bad.");
			if (d1.size_ != amount) throw std::runtime_error("Size is bad.");

			if (a1.capacity_ < amount) throw std::runtime_error("Capacity is bad.");
			if (b1.capacity_ < amount) throw std::runtime_error("Capacity is bad.");
			if (c1.capacity_ < amount) throw std::runtime_error("Capacity is bad.");
			if (d1.capacity_ < amount) throw std::runtime_error("Capacity is bad.");

			for (u64 i = 0; i < amount; i++)
			{
				if (a1.data_[i] != 0) throw std::runtime_error("Data is bad.");
				if (b1.data_[i] != 0) throw std::runtime_error("Data is bad.");
				if (c1.data_[i] != 0) throw std::runtime_error("Data is bad.");
				if (d1.data_[i] != 0) throw std::runtime_error("Data is bad.");
			}

			output << ".\t.\t" << GREEN << "PASSED" << RESET << " Move constructor.\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t" << RED << "FAILED" << RESET << " Move constructor: " << e.what() << '\n';
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

			dynamic_array<i32> a2(amount, 0);
			dynamic_array<f32> b2(amount, 0);
			dynamic_array<b08> c2(amount, 0);
			dynamic_array<u64> d2(amount, 0);

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

			for (u64 i = 0; i < amount; i++)
			{
				if (a2.data_[i] != a12.data_[i]) throw std::runtime_error("Data is bad.");
				if (b2.data_[i] != b12.data_[i]) throw std::runtime_error("Data is bad.");
				if (c2.data_[i] != c12.data_[i]) throw std::runtime_error("Data is bad.");
				if (d2.data_[i] != d12.data_[i]) throw std::runtime_error("Data is bad.");
			}

			output << ".\t.\t" << GREEN << "PASSED" << RESET << " Copy constructor.\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t" << RED << "FAILED" << RESET << " Copy constructor: " << e.what() << '\n';
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

			dynamic_array<i32> a2(amount, 0);
			dynamic_array<f32> b2(amount, 0);
			dynamic_array<b08> c2(amount, 0);
			dynamic_array<u64> d2(amount, 0);

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

			for (u64 i = 0; i < amount; i++)
			{
				if (a2.data_[i] != a12.data_[i]) throw std::runtime_error("Data is bad.");
				if (b2.data_[i] != b12.data_[i]) throw std::runtime_error("Data is bad.");
				if (c2.data_[i] != c12.data_[i]) throw std::runtime_error("Data is bad.");
				if (d2.data_[i] != d12.data_[i]) throw std::runtime_error("Data is bad.");
			}

			output << ".\t.\t" << GREEN << "PASSED" << RESET << " operator = (const darr&).\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t" << RED << "FAILED" << RESET << " operator = (const darr&): " << e.what() << '\n';
			result = false;
			tests_failed++;
		}
	}
	output << ".\t.\t.\t\n";

	// non-trivial types
	output << ".\tTesting construction with non-primitive types...\n";

	// no default constructor
	{
		output << ".\t.\tTesting construction with no-default-constructor type...\n";

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
			dynamic_array<no_default> a(amount, 0);

			if (a.data_ == nullptr) throw std::runtime_error("Data is null.");

			if (a.size_ != amount) throw std::runtime_error("Size is bad.");

			if (a.capacity_ < amount) throw std::runtime_error("Capacity is bad.");

			no_default* a_ptr = a.data_;

			for (u64 i = 0; i < amount; i++)
			{
				if (a_ptr[i].data_ != 0) throw std::runtime_error("Data is bad.");
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
			dynamic_array<no_default> a(amount, 0);

			dynamic_array<no_default> a1{ std::move(a) };

			if (a.data_ != nullptr) throw std::runtime_error("Data is not null.");

			if (a.size_ != 0) throw std::runtime_error("Size is not null.");

			if (a.capacity_ != 0) throw std::runtime_error("Capacity is not null.");

			if (a1.data_ == nullptr) throw std::runtime_error("Data is null.");

			if (a1.size_ != amount) throw std::runtime_error("Size is bad.");

			if (a1.capacity_ < amount) throw std::runtime_error("Capacity is bad.");

			for (u64 i = 0; i < amount; i++)
			{
				if (a1.data_[i].data_ != 0) throw std::runtime_error("Data is bad.");
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
			dynamic_array<no_default> a{};

			dynamic_array<no_default> a1{ a };

			if (a.data_ == a1.data_) throw std::runtime_error("Data is same.");

			if (a.size_ != a1.size_) throw std::runtime_error("Size is bad.");

			if (a.capacity_ != a1.capacity_) throw std::runtime_error("Capacity is bad.");

			dynamic_array<no_default> a2(amount, 0);

			dynamic_array<no_default> a12{ a2 };

			if (a2.data_ == a12.data_) throw std::runtime_error("Data is same.");

			if (a2.size_ != a12.size_) throw std::runtime_error("Size is bad.");

			if (a2.capacity_ != a12.capacity_) throw std::runtime_error("Capacity is bad.");

			for (u64 i = 0; i < amount; i++)
			{
				if (a2.data_[i].data_ != a12.data_[i].data_) throw std::runtime_error("Data is bad.");
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
			dynamic_array<no_default> a{};

			dynamic_array<no_default> a1{ a };

			if (a.data_ == a1.data_) throw std::runtime_error("Data is same.");

			if (a.size_ != a1.size_) throw std::runtime_error("Size is bad.");

			if (a.capacity_ != a1.capacity_) throw std::runtime_error("Capacity is bad.");

			dynamic_array<no_default> a2(amount, 0);

			dynamic_array<no_default> a12{ a2 };

			if (a2.data_ == a12.data_) throw std::runtime_error("Data is same.");

			if (a2.size_ != a12.size_) throw std::runtime_error("Size is bad.");

			if (a2.capacity_ != a12.capacity_) throw std::runtime_error("Capacity is bad.");

			for (u64 i = 0; i < amount; i++)
			{
				if (a2.data_[i].data_ != a12.data_[i].data_) throw std::runtime_error("Data is bad.");
			}

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " operator = (const darr&).\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " operator = (const darr&): " << e.what() << '\n';
			result = false;
			tests_failed++;
		}
	}

	// no copy constructor
	{
		output << ".\t.\tTesting construction with no-copy-constructor type...\n";

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

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " Default constructor.\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " Default constructor: " << e.what() << '\n';
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

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " Move constructor.\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " Move constructor: " << e.what() << '\n';
			result = false;
			tests_failed++;
		}
	}

	// no move constructor
	{
		output << ".\t.\tTesting construction with no-move-constructor type...\n";

		struct no_move
		{
			i32 data_ = 10;

			no_move() noexcept {};
			no_move(i32 a) noexcept { data_ = a;  };
			no_move(const no_move& o) noexcept { data_ = o.data_; };
			no_move(no_move&&) noexcept = delete;
		};

		// default constructor
		try
		{
			dynamic_array<no_move> a{};

			if (a.size_ != 0) throw std::runtime_error("Size is not null.");

			if (a.capacity_ != dynamic_array<no_move>::PREALLOCATED_CAPACITY) throw std::runtime_error("Capacity is bad.");

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " Default constructor.\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " Default constructor: " << e.what() << '\n';
			result = false;
			tests_failed++;
		}

		// move constructor
		try
		{
			dynamic_array<no_move> a{};

			dynamic_array<no_move> a1{ std::move(a) };

			if (a.data_ != nullptr) throw std::runtime_error("Data is not null.");

			if (a1.data_ == nullptr) throw std::runtime_error("Data is null.");

			output << ".\t.\t.\t" << GREEN << "PASSED" << RESET << " Move constructor.\n";
			tests_passed++;
		}
		catch (std::exception e)
		{
			output << ".\t.\t.\t" << RED << "FAILED" << RESET << " Move constructor: " << e.what() << '\n';
			result = false;
			tests_failed++;
		}
	}
	output << ".\t.\t.\t.\t\n";

	output << ".\tTesting basic operations...\n";



	return result;
}
