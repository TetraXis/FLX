#include <iostream>

#include "flx/imp_core.hpp"

int main()
{
    std::cout << "FLX TEST.\n";
    std::cout << FLX_VERSION << '\n';
    std::cout << IMP_COMPILER_ << '\n';
    std::cout << __cplusplus << '\n';
    return 0;
}
