#include <iostream>
#include <vector>
#include <sstream>
#include <type_traits>
#include <string>

#define FLX_ALL_MEMBERS_ARE_PUBLIC

//#include "flx_dynamic_array.hpp"
#include "flx_unique_ptr.hpp"
#include "flx_dynamic_array.hpp"

#define META_TESTS 10
#define TESTS 10'000'000

struct test_str
{
	int a = 10;
	int* data = nullptr;

	test_str()
	{
		data = new int[10];
		std::cout << "new\n";
	}

	test_str(test_str&& other) noexcept
	{
		data = other.data;
		other.data = nullptr;
	}

	~test_str()
	{
		if (data)
		{
			delete[] data;
			std::cout << "delete[]\n";
		}
		std::cout << "nullptr delete[]\n";
	}

	//test_str(test_str&&) = default;
};

class Node {
public:
	Node* parent;
	std::vector<Node*> children;

	explicit Node(Node* p = nullptr) : parent(p) {
		if (parent) parent->children.push_back(this);
	}

	// "Perfect" move constructor
	Node(Node&& other) noexcept
		: parent(other.parent), children(std::move(other.children))
	{
		std::cout << "move\n";

		// Update children's parent pointers
		for (Node* child : children) {
			child->parent = this;
		}
		// Neuter the source
		other.parent = nullptr;
		other.children.clear();
	}

	// "Perfect" move constructor
	Node(const Node& other) noexcept
		
	{
		std::cout << "copy\n";
	}

	~Node() {
		// Critical: Clear parent pointer from all children
		for (Node* child : children) {
			child->parent = nullptr;  // Prevent dangling pointers
		}
	}
};

using namespace flx;

//using test_t = std::vector<Node>;
using test_t = flx::dynamic_array<Node>;

#include "D:\C++\Tools\timer.h"

int main()
{
	//test_t arr;

	//// Create a parent-child relationship
	//arr.emplace_back(nullptr);  // NodeA at index 0
	//arr.emplace_back(&arr[0]);  // NodeB at index 1 (parent=NodeA)

	//std::cout << "Before reallocation:\n";
	//std::cout << "NodeB's parent: " << arr[1].parent << "\n";  // Valid pointer

	//// Trigger reallocation
	//arr.reallocate();

	//std::cout << "After reallocation:\n";
	//// !!! CRASH HERE !!! - Accessing moved-from NodeB_old.parent (dangling pointer)
	//std::cout << "NodeB's old parent: " << arr[1].parent << "\n";

	//return 0;


	flx::dynamic_array<std::string> a;

	a.emplace_back("hello");
	a.emplace_back("hello");
	a.emplace_back("hello");
	a.emplace_back("hello");
	a.emplace_back("hello");
	a.emplace_back("hello");
	a.emplace_back("hello");
	a.emplace_back("hello");
	a.emplace_back("hello");

	/*std::stringstream SS;
	std::stringstream ss;
	u64 sum = 0;

	for (size_t II = 0; II < META_TESTS; II++)
	{


		timer t;

		t.start();
		for (size_t I = 0; I < TESTS; I++)
		{
			test_t a;

			for (size_t i = 0; i < 20; i++)
			{
				a.emplace_back();
			}

			ss << a[19].a;
		}
		t.stop();
		
		SS << t.elapsed_milliseconds() << "ms.\n";
		sum += t.elapsed_milliseconds();
	}

	std::cout << ss.str() << '\n';
	std::cout << SS.str() << '\n';

	std::cout << "AVG:\n";
	std::cout << f64(sum) / META_TESTS << '\n';*/
}

/*

std::vector 436ms
flx::dynamic_array 228ms

std::vector 4330.4ms
flx::dynamic_array 2675.0ms

*/