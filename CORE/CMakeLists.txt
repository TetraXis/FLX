cmake_minimum_required(VERSION 4.0)

add_library(flx_core INTERFACE
        include/flx/core.hpp
        include/flx/core_env.hpp
        include/flx/core_opt.hpp)

target_include_directories(flx_core INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_custom_target(flx_core_install ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/include/flx
        ${FLX_INSTALL_DIR}/CORE/include/flx
        COMMENT "Copying CORE headers to INSTALL/CORE/include/flx"
)