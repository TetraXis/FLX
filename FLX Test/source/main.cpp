#include <iostream>

#include "flx/type_traits.hpp"

int main()
{
	int a = 1;
	flx::add_lvalue_reference<int> b = a;
}