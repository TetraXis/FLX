#include "flx/core.hpp"
//
//import flx.assert;
//import flx.terminate;
//import flx.memory;
//import flx.type_traits;

import flx;

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

int main()
{
    using namespace flx;

    const c8* ver = "FLX v." FLX_VERSION " built successfully.\n";

    const char* cpp = "CPP: " TOSTRING(__cplusplus) ".\n";

#if FLX_ENV_COMPILER == FLX_ENV_COMPILER_MSVC

    const c8* compiler = "MSVC v." _MSC_VER ".\n";

#elif FLX_ENV_COMPILER == FLX_ENV_COMPILER_GCC

    const c8* compiler = "GCC v." __GNUC__ ".\n";

#elif FLX_ENV_COMPILER == FLX_ENV_COMPILER_CLANG

    const c8* compiler = "Clang v." __clang_version__  ".\n";

#else

    const c8* compiler = "Unknown.\n";

#endif

    flx::crt::write(1, ver, flx::crt::strlen(ver));
    flx::crt::write(1, cpp, flx::crt::strlen(cpp));
    flx::crt::write(1, compiler, flx::crt::strlen(compiler));

    return 0;
}

#undef STRINGIFY
#undef TOSTRING