module;

// Core will gather test results from all tests.

#include "flx/core.hpp"

#include <map>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>

export module test.core;

export namespace test
{
	using std::map, std::string, std::vector;

	struct result
	{
		bool pass = false;
		string error = "NULL";
	};

	//         group   subgroup
	inline map<string, map<string, vector<result>>> results;
	inline string group = "NULL";
	inline string subgroup = "NULL";
	inline string error = "NULL";

	inline void push(const string& group_, const string& subgroup_, bool pass_, const string& error_)
	{
		test::results[group_][subgroup_].emplace_back(pass_, error_);
		return;
	}

	inline void push(bool pass_, const string& error_ = test::error)
	{
		test::results[test::group][test::subgroup].emplace_back(pass_, error_);
		return;
	}

	inline bool check(const bool expected, const string& possible_error = test::error)
	{
		if (expected)
		{
			test::results[test::group][test::subgroup].emplace_back(expected, "NULL");
		}
		else
		{
			test::results[test::group][test::subgroup].emplace_back(expected, possible_error);
		}
		return expected;
	}

	inline void print_results()
	{
		constexpr unsigned long long GROUP_WIDTH = 16;
		constexpr unsigned long long SUBGROUP_WIDTH = 32;
		constexpr unsigned long long PASS_WIDTH = 8;
		constexpr unsigned long long ERROR_WIDTH = 64;

		constexpr const char* RED   = "\033[31m";
		constexpr const char* GREEN = "\033[32m";
		constexpr const char* CYAN  = "\033[36m";
		constexpr const char* RESET = "\033[0m";

		std::stringstream ss{};
		unsigned long long tests_amount = 0;
		unsigned long long tests_passed = 0;
		unsigned long long subgroup_tests_passed = 0;
		unsigned long long tests_failed = 0;

#if FLX_CFG_RELEASE && FLX_CFG_DEBUG
		ss << "Testing FLX v." FLX_VERSION " in BOTH.\n\n";
#elif FLX_CFG_RELEASE
		ss << "Testing FLX v." FLX_VERSION " in RELEASE.\n\n";
#elif FLX_CFG_DEBUG
		ss << "Testing FLX v." FLX_VERSION " in DEBUG.\n\n";
#else
		ss << "Testing FLX v." FLX_VERSION " in NONE.\n\n";
#endif

		ss
			<< std::left
			//<< std::left << std::setw(GROUP_WIDTH) << "Group"
			<< std::setw(SUBGROUP_WIDTH)	<< "Subgroup"
			<< std::setw(PASS_WIDTH)		<< "Pass"
			<< std::setw(ERROR_WIDTH)		<< "Error"
			<< '\n';

		for (const auto& [group_, subgroups_] : test::results)
		{
			ss << '\n' << CYAN << group_ << RESET << '\n';

			for (const auto& [subgroup_, results_] : subgroups_)
			{
				subgroup_tests_passed = 0;
				for (const auto& result_ : results_)
				{
					++tests_amount;
					if (result_.pass)
					{
						++tests_passed;
						++subgroup_tests_passed;
					}
					else
					{
						++tests_failed;
						ss
							<< std::setw(SUBGROUP_WIDTH)	<< subgroup_
							<< RED << std::setw(PASS_WIDTH)	<< "FAIL" << RESET
							<< std::setw(ERROR_WIDTH)		<< result_.error
							<< '\n';
					}
				}

				string temp_amount = "x" + std::to_string(subgroup_tests_passed) + '\t';

				ss
				<< std::setw(SUBGROUP_WIDTH - (temp_amount.size()))	<< subgroup_ << temp_amount
				<< GREEN << std::setw(PASS_WIDTH)					<< "PASS" << RESET
				<< '\n';
			}
		}

		ss << '\n';
#if defined(NDEBUG)
		ss << "Tested FLX v." FLX_VERSION " in RELEASE.\n";
#else
		ss << "Tested FLX v." FLX_VERSION " in DEBUG.\n";
#endif

		ss << "Tests done:\t" << tests_amount << '\n'
			<< "Tests passed:\t" << tests_passed << '\n'
			<< "Tests failed:\t" << tests_failed << '\n';

		if (tests_failed == 0)
		{
			ss << GREEN << "TEST PASSED.\n" << RESET;
		}
		else
		{
			ss << RED << "TEST FAILED.\n" << RESET;
		}

		std::cout << ss.str();
	} // print_results

} // namespace test
