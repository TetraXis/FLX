#include "flx/core.hpp"
#include <iostream>

#include <type_traits>
#include <utility>

#include <stdio.h>

int main()
{
    //int a;
    flx::crt::write(0, "10", 2);

    char arr[10];

    flx::crt::read(0, arr, 2);



    std::cout << arr[0] << arr[1];

    return 0;
}
