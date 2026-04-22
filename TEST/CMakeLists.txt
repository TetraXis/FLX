cmake_minimum_required(VERSION 3.15)

add_executable(flx_test main.cpp
        test/type_traits.hpp
        test/core.hpp)

add_dependencies(flx_test flx_core_install)

target_include_directories(flx_test PRIVATE
        ${FLX_INSTALL_DIR}/CORE/include
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(flx_test PRIVATE
        $<$<CONFIG:Debug>:FLX_OPT_DEBUG>
        $<$<CONFIG:Release>:FLX_OPT_RELEASE>
)

set_target_properties(flx_test PROPERTIES
        CXX_STANDARD 26
        CXX_STANDARD_REQUIRED ON
)