# 2026-Apr-24 23:58
# This file absolutly destroyed my will to live. I hate CMake. It took me ~6 hours to configure this bs.
# If my life as a C++ programmer would involve more CMake than C++ (like it did today), I would rather die.

cmake_minimum_required(VERSION 3.31)
project(test_core LANGUAGES CXX)

if(NOT FLX_INSTALL_BASE_DIR)
    get_filename_component(TEST_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)
    set(FLX_INSTALL_BASE_DIR "${TEST_SOURCE_DIR}/../../INSTALL" CACHE PATH "Installation root" FORCE)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(INSTALL_CONFIG_DIR "Release")
else()
    set(INSTALL_CONFIG_DIR "Debug")
endif()

set(INSTALLED_CORE_DIR     "${FLX_INSTALL_BASE_DIR}/${INSTALL_CONFIG_DIR}/CORE")
set(INSTALLED_CORE_INCLUDE "${INSTALLED_CORE_DIR}/include")          # parent of 'flx'
set(INSTALLED_CORE_MODULES "${INSTALLED_CORE_DIR}/include/flx")      # where .cppm files are
set(INSTALLED_CORE_LIB     "${INSTALLED_CORE_DIR}/lib")


file(GLOB_RECURSE CORE_MODULE_SOURCES CONFIGURE_DEPENDS
    "${INSTALLED_CORE_MODULES}/*.cppm"
)

file(GLOB TEST_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)
file(GLOB_RECURSE TEST_MODULE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cppm"
)

add_library(core_rebuild STATIC)

target_include_directories(core_rebuild PRIVATE
    "${INSTALLED_CORE_INCLUDE}"
)

target_sources(core_rebuild
    PUBLIC
        FILE_SET CXX_MODULES
        BASE_DIRS ${INSTALLED_CORE_DIR}/include
        FILES ${CORE_MODULE_SOURCES}
)

file(GLOB CORE_LIBS "${INSTALLED_CORE_LIB}/*.lib" "${INSTALLED_CORE_LIB}/*.a")
target_link_libraries(core_rebuild PUBLIC ${CORE_LIBS})

add_library(test_modules STATIC)

target_include_directories(test_modules PRIVATE
    "${INSTALLED_CORE_INCLUDE}"
)

target_sources(test_modules
    PUBLIC
        FILE_SET CXX_MODULES
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
        FILES ${TEST_MODULE_SOURCES}
)

target_link_libraries(test_modules PUBLIC core_rebuild)

add_executable(test_core_exe)
target_sources(test_core_exe PRIVATE ${TEST_SOURCES})
target_link_libraries(test_core_exe PRIVATE test_modules core_rebuild)
target_include_directories(test_core_exe PRIVATE "${INSTALLED_CORE_INCLUDE}")



add_dependencies(core_rebuild install_flx_core)
add_dependencies(test_modules install_flx_core)
add_dependencies(test_core_exe install_flx_core)



set(common_options $<$<CXX_COMPILER_ID:GNU>:-fmodules-ts>)
target_compile_features(core_rebuild PRIVATE cxx_std_26)
target_compile_options(core_rebuild PRIVATE ${common_options})
target_compile_features(test_modules PRIVATE cxx_std_26)
target_compile_options(test_modules PRIVATE ${common_options})
target_compile_features(test_core_exe PRIVATE cxx_std_26)
target_compile_options(test_core_exe PRIVATE ${common_options})

set_target_properties(core_rebuild test_modules test_core_exe PROPERTIES
    CXX_STANDARD 26
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)