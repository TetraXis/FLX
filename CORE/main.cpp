#include "flx/core.hpp"

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

    const char* ver = "FLX v." FLX_VERSION " built successfully.\n";

    const char* cpp = "CPP: " TOSTRING(__cplusplus) ".\n";

#if FLX_ENV_COMPILER == FLX_ENV_COMPILER_MSVC

    const char* compiler = "MSVC v." _MSC_VER ".\n";

#elif FLX_ENV_COMPILER == FLX_ENV_COMPILER_GCC

    const char* compiler = "GCC v." __GNUC__ ".\n";

#elif FLX_ENV_COMPILER == FLX_ENV_COMPILER_CLANG

    const char* compiler = "Clang v." __clang_version__  ".\n";

#else

    const char* compiler = "Unknown.\n";

#endif


#if FLX_CFG_RELEASE

    const char* mode = "RELEASE\n";

#else

    const char* mode = "RELEASE\n";

#endif

    flx::crt::write(1, ver, flx::crt::strlen(ver));
    flx::crt::write(1, cpp, flx::crt::strlen(cpp));
    flx::crt::write(1, compiler, flx::crt::strlen(compiler));
    flx::crt::write(1, mode, flx::crt::strlen(mode));

    return 0;
}

#undef STRINGIFY
#undef TOSTRING