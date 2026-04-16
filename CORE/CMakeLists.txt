cmake_minimum_required(VERSION 4.0)

add_library(flx_core INTERFACE
        include/flx/core.hpp
        include/flx/core_env.hpp
        include/flx/core_opt.hpp
        include/flx/core_cfg.hpp
        include/flx/assert.hpp
        include/flx/terminate.hpp
        include/flx/core_has.hpp
        include/flx/core_crt.hpp
        include/flx/core_crt_assert.hpp
        include/flx/core_crt_math.hpp
        include/flx/core_crt_stdio.hpp
        include/flx/core_crt_stdlib.hpp
        include/flx/core_crt_string.hpp
        include/flx/core_crt_time.hpp
        include/flx/core_crt_complex.hpp
        include/flx/core_crt_ctype.hpp
        include/flx/core_crt_errno.hpp
        include/flx/core_crt_fenv.hpp
        include/flx/core_crt_float.hpp
        include/flx/core_crt_inttypes.hpp
        include/flx/core_crt_iso646.hpp
        include/flx/core_crt_limits.hpp
        include/flx/core_crt_locale.hpp
        include/flx/core_crt_setjmp.hpp
        include/flx/core_crt_signal.hpp
        include/flx/core_crt_stdarg.hpp
        include/flx/core_crt_stdbool.hpp
        include/flx/core_crt_stddef.hpp
        include/flx/core_crt_stdint.hpp
        include/flx/core_crt_tgmath.hpp
        include/flx/core_crt_wchar.hpp
        include/flx/core_crt_wctype.hpp)

target_include_directories(flx_core INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(flx_core INTERFACE
        $<$<CONFIG:Debug>:FLX_OPT_DEBUG>
        $<$<CONFIG:Release>:FLX_OPT_RELEASE>
)

add_custom_target(flx_core_install ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/include/flx
        ${FLX_INSTALL_DIR}/CORE/include/flx
        COMMENT "Copying CORE headers to INSTALL/CORE/include/flx"
)