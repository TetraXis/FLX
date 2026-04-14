#include "flx/core.hpp"

#include "flx/assert.hpp"

#include "stdio.h"

int main()
{
    printf("Installed FLX version: " FLX_VERSION "\n");

    flx::assert(false, "balls\n");

    return 0;
}
