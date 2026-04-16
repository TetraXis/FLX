#include "flx/core.hpp"

#if FLX_CFG_DEBUG
int a = 0;
#endif

#if FLX_CFG_RELEASE
int a = 1;
#endif

#include <iostream>

int main()
{
    std::cout << a;

    return 0;
}
