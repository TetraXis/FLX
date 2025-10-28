#ifndef FLX_TESTS_HPP
#define FLX_TESTS_HPP

#define FLX_ALL_MEMBERS_ARE_PUBLIC

#include "flx/imp_core.hpp"

#include <sstream>

FLX_BEGIN_

namespace test
{
	FLX_API_ constexpr u64 VOLUME = 100;

	FLX_API_ extern std::stringstream output;
	FLX_API_ extern std::string testee;
	FLX_API_ extern std::string header;
	FLX_API_ extern std::string chunk;
	FLX_API_ extern u64 tests_passed;
	FLX_API_ extern u64 tests_failed;

	FLX_API_ extern u64 called_def_constructors;
	FLX_API_ extern u64 called_custom_constructors;
	FLX_API_ extern u64 called_copy_constructors;
	FLX_API_ extern u64 called_move_constructors;
	FLX_API_ extern u64 called_copy_assigments;
	FLX_API_ extern u64 called_move_assigments;
	FLX_API_ extern u64 called_destructors;
	FLX_API_ extern std::string called_result;

	FLX_API_ extern bool result_header;
	FLX_API_ extern bool result_chunk;

	FLX_API_ struct test_str
	{
		u64 data = 0xDEADDEADDEADDEAD;

		test_str() noexcept { data = 0xCCCCCCCCCCCCCCCC; called_def_constructors++; }
		test_str(u64 val) noexcept { called_custom_constructors++; data = val; }
		test_str(const test_str& other) noexcept { data = other.data; called_copy_constructors++; }
		test_str(test_str&& other) noexcept { data = other.data; other.data = 0xCCCCCCCCCCCCCCCC; called_move_constructors++; }
		test_str& operator= (const test_str& other) noexcept { data = other.data; called_copy_assigments++; return *this; }
		test_str& operator= (test_str&& other) noexcept { data = other.data; other.data = 0xCCCCCCCCCCCCCCCC; called_move_assigments++; return *this; }
		~test_str() noexcept { data = 0xCCCCCCCCCCCCCCCC; called_destructors++; }

		bool operator == (const test_str& other) const noexcept { return data == other.data; }
		bool operator != (const test_str& other) const noexcept { return data != other.data; }
	};

	void pass_(const std::string&);
	void pass_();
	void fail_(const std::string&);
	void fail_();

	void header_status_();
	void chunk_status_();

	void reset_calls_();
	bool test_calls_(u64, u64, u64, u64, u64, u64, u64);

	FLX_API_ bool test_self();

	FLX_API_ bool test_flx();
	
	FLX_API_ bool test_new();
	FLX_API_ bool test_type_traits();
	FLX_API_ bool test_concepts();
	FLX_API_ bool test_utility();
	FLX_API_ bool test_memory();
	FLX_API_ bool test_dynamic_array();
}

FLX_END_

#endif // FLX_TESTS_HPP