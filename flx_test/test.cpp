#include <iostream>
#include <vector>
#include <sstream>
#include <type_traits>
#include <string>
#include <unordered_set>
#include <map>

#define FLX_ALL_MEMBERS_ARE_PUBLIC

#include "flx_unique_ptr.hpp"
#include "flx_dynamic_array.hpp"

using namespace flx;

#define META_TESTS 10
#define TESTS 10'000'000

/*

flx no destr
AVG:
2596.6

flx destr
AVG:
2604

std
AVG:
4363.7





flx no destr
AVG:
16943

flx destr
AVG:
17492.3

std
AVG:
20273.5






flx no destr
AVG:
2595.7

flx destr
AVG:
2588.4

std
AVG:
4344.6






*/

struct test_str
{
	int a = 0;
	//int* data;

	test_str() noexcept = default;
	//{
	//	data = new int[10];
	//}

	test_str(test_str&& other) noexcept = default;
	//	:data(other.data)
	//{
	//	other.data = nullptr;
	//}

	~test_str() noexcept = default;
	//{
	//	delete[] data;
	//}

	//test_str(test_str&&) = default;
};

//struct test_str
//{
//	static constexpr u64 SIZE = 10000;
//
//	int a = 10;
//	std::vector<int*> data;
//
//	test_str()
//	{
//		for (size_t i = 0; i < SIZE; i++)
//		{
//			data.emplace_back(new int[100]);
//		}
//	}
//
//	test_str(test_str&& other) noexcept
//		: data(std::move(other.data))
//	{
//		other.data.clear();
//	}
//
//	test_str(const test_str& other) noexcept
//	{
//		data = other.data;
//	}
//
//	~test_str()
//	{
//		for (size_t i = 0; i < data.size(); i++)
//		{
//			if (data[i])
//			{
//				delete[] data[i];
//			}
//		}
//	}
//
//	//test_str(test_str&&) = default;
//};

//class Node {
//public:
//	Node* parent;
//	std::vector<Node*> children;
//
//	explicit Node(Node* p = nullptr) : parent(p) {
//		if (parent) parent->children.push_back(this);
//	}
//
//	// "Perfect" move constructor
//	Node(Node&& other) noexcept
//		: parent(other.parent), children(std::move(other.children))
//	{
//		std::cout << "move\n";
//
//		// Update children's parent pointers
//		for (Node* child : children) {
//			child->parent = this;
//		}
//		// Neuter the source
//		other.parent = nullptr;
//		other.children.clear();
//	}
//
//	// "Perfect" move constructor
//	Node(const Node& other) noexcept
//		
//	{
//		std::cout << "copy\n";
//	}
//
//	~Node() {
//		// Critical: Clear parent pointer from all children
//		for (Node* child : children) {
//			child->parent = nullptr;  // Prevent dangling pointers
//		}
//	}
//};
//
//class NetworkConnection {
//	static std::unordered_set<NetworkConnection*> live_connections;
//	int socket_fd;
//public:
//	explicit NetworkConnection(int fd) : socket_fd(fd) {
//		live_connections.insert(this);
//		std::cout << "Connection " << this << " created (fd=" << socket_fd << ")\n";
//	}
//
//	// Correct noexcept move constructor
//	NetworkConnection(NetworkConnection&& other) noexcept
//		: socket_fd(other.socket_fd) {
//		live_connections.erase(&other);
//		live_connections.insert(this);
//		other.socket_fd = -1;  // Invalidate source
//		std::cout << "Connection moved " << &other << " -> " << this << "\n";
//	}
//
//	~NetworkConnection() {
//		live_connections.erase(this);
//		if (socket_fd != -1) {
//			std::cout << "CLOSING fd=" << socket_fd << " (" << this << ")\n";
//			// Real code would call close(socket_fd) here
//		}
//	}
//
//	static void print_connections() {
//		std::cout << "Live connections: ";
//		for (auto conn : live_connections) {
//			std::cout << conn << " ";
//		}
//		std::cout << "\n";
//	}
//};
//
//std::unordered_set<NetworkConnection*> NetworkConnection::live_connections;


using test_t_std = std::vector			< test_str >;
using test_t_flx = flx::dynamic_array	< test_str >;


using test_t = std::vector<test_str>;
//using test_t = flx::dynamic_array<test_str>;

#include "D:\C++\Tools\timer.h"

int main()
{
	std::stringstream SS;
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
	std::cout << f64(sum) / META_TESTS << '\n';

}


//int main()
//{
//	std::stringstream ss;
//	double flx_time = 0;
//	double std_time = 0;
//
//	for (size_t II = 0; II < META_TESTS; II++)
//	{
//		timer t;
//
//		t.start();
//		for (size_t I = 0; I < TESTS; I++)
//		{
//			test_t_std a;
//
//			for (size_t i = 0; i < 20; i++)
//			{
//				a.emplace_back();
//			}
//
//			ss << a[19].a;
//		}
//		t.stop();
//		std_time += t.elapsed_milliseconds();
//
//		t.start();
//		for (size_t I = 0; I < TESTS; I++)
//		{
//			test_t_flx a;
//
//			for (size_t i = 0; i < 20; i++)
//			{
//				a.emplace_back();
//			}
//
//			ss << a[19].a;
//		}
//		t.stop();
//		flx_time += t.elapsed_milliseconds();
//	}
//
//	std::cout << ss.str() << '\n';
//
//	std::cout << "STD AVG:\n";
//	std::cout << std_time / META_TESTS << '\n';
//
//	std::cout << "FLX AVG:\n";
//	std::cout << flx_time / META_TESTS << '\n';
//
//	std::cout << "\a";
//}

/*

std::vector 436ms
flx::dynamic_array 228ms

std::vector 4330.4ms
flx::dynamic_array 2675.0ms

test_str =====

no destructors

STD AVG:
19677.5
FLX AVG:
17157.5

adding destructors

STD AVG:
19707.6
FLX AVG:
17306.4

string =====

no destructors

STD AVG:
2275.3
FLX AVG:
1878.2

STD AVG:
1441.35
FLX AVG:
1017.15

adding destructors

STD AVG:
2439.9
FLX AVG:
1720

STD AVG:
1295.35
FLX AVG:

FAT =====

no destructors

STD AVG:
165.65
FLX AVG:
157.4

adding destructors

STD AVG:
167.9
FLX AVG:
156.9



*/