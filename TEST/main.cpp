#define FLX_OPT_FORCE_DEBUG

#include "flx/core.hpp"

#include "flx/assert.hpp"

#include "stdio.h"

#include <type_traits>

int main()
{
    printf("Installed FLX version: " FLX_VERSION "\n");

    flx::assert(std::is_same_v<flx::sszt, signed long long>, "balls balls balls\nballs balls balls\nballs balls balls\n");

    return 0;
}
