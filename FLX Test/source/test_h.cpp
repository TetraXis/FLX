#include "test_h.h"
#include <iostream>

using namespace flx;

void test()
{
	flx::last_error = "testing...";

	flx::terminate();
}
