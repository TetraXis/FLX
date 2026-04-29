# 2026-Apr-24 23:58
# These two files absolutly destroyed my will to live. I hate CMake. It took me ~6 hours to configure this bs.
# If my life as a C++ programmer would involve more CMake than C++ (like it did today), I would rather die.
#
# C++26: barely supported.
# CMake: pile of shitty spaghetti
# Modules: barely supported. They were introduced in C++20, it's been 6 fucking years.

cmake_minimum_required(VERSION 3.31)
project(flx_core LANGUAGES CXX)

# make proper names
if(WIN32)
    set(CMAKE_STATIC_LIBRARY_PREFIX "")
    set(CMAKE_STATIC_LIBRARY_SUFFIX ".lib")
endif()

get_filename_component(FLX_CORE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)

if(NOT FLX_INSTALL_BASE_DIR)
    set(FLX_INSTALL_BASE_DIR "${FLX_CORE_SOURCE_DIR}/../INSTALL" CACHE PATH "Installation root" FORCE)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(INSTALL_CONFIG_DIR "Release")
else()
    set(INSTALL_CONFIG_DIR "Debug")
endif()

set(FLX_INSTALL_DIR "${FLX_INSTALL_BASE_DIR}/${INSTALL_CONFIG_DIR}/CORE")
set(FLX_INSTALL_LIB_DIR "${FLX_INSTALL_DIR}/lib")
set(FLX_INSTALL_INCLUDE_DIR "${FLX_INSTALL_DIR}/include/flx")

file(GLOB FLX_CORE_SOURCES CONFIGURE_DEPENDS
    "${FLX_CORE_SOURCE_DIR}/source/*.cpp"
)
file(GLOB_RECURSE FLX_CORE_PUBLIC_HPP CONFIGURE_DEPENDS
    "${FLX_CORE_SOURCE_DIR}/include/flx/*.hpp"
)
file(GLOB_RECURSE FLX_CORE_MODULES CONFIGURE_DEPENDS
    "${FLX_CORE_SOURCE_DIR}/include/flx/*.cppm"
)

set(ALL_FLX_LIBS "")
set(modules_attached FALSE)

# one .lib for each .cpp

foreach(src_file ${FLX_CORE_SOURCES})
    get_filename_component(lib_name ${src_file} NAME_WE)
    set(lib_target "${lib_name}")

    add_library(${lib_target} STATIC ${src_file})
    list(APPEND ALL_FLX_LIBS ${lib_target})

    set_target_properties(${lib_target} PROPERTIES
        ARCHIVE_OUTPUT_NAME "${lib_name}"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    )

    # Attach module interfaces to the first library only
    if(NOT modules_attached)
        target_sources(${lib_target}
            PUBLIC
                FILE_SET CXX_MODULES
                BASE_DIRS "${FLX_CORE_SOURCE_DIR}/include"
                FILES ${FLX_CORE_MODULES}
        )
        set(modules_attached TRUE)
    endif()

    target_compile_features(${lib_target} PUBLIC cxx_std_26)
    set_target_properties(${lib_target} PROPERTIES
        CXX_STANDARD 26
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
    )
    target_compile_options(${lib_target} PRIVATE $<$<CXX_COMPILER_ID:GNU>:-fmodules-ts>)

    target_include_directories(${lib_target} PUBLIC
        $<BUILD_INTERFACE:${FLX_CORE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${FLX_INSTALL_INCLUDE_DIR}>
    )
endforeach()

# dummy executable so Visual Studio woudl see it
add_executable(flx_main dummy_main.cpp)
if(ALL_FLX_LIBS)
    target_link_libraries(flx_main PRIVATE ${ALL_FLX_LIBS})
endif()

target_compile_features(flx_main PRIVATE cxx_std_26)
set_target_properties(flx_main PROPERTIES
    CXX_STANDARD 26
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
target_compile_options(flx_main PRIVATE $<$<CXX_COMPILER_ID:GNU>:-fmodules-ts>)

add_dependencies(flx_main install_flx_core)

# default install is aids, install manualy

add_custom_target(install_flx_core ALL
    DEPENDS ${ALL_FLX_LIBS}
    COMMENT "Installing flx_core to ${FLX_INSTALL_DIR}"
)

foreach(lib ${ALL_FLX_LIBS})
    add_custom_command(TARGET install_flx_core POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${FLX_INSTALL_LIB_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:${lib}>"
            "${FLX_INSTALL_LIB_DIR}/$<TARGET_FILE_NAME:${lib}>"
        VERBATIM
    )
endforeach()

# copy the whole include dir

add_custom_command(TARGET install_flx_core POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${FLX_INSTALL_INCLUDE_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${FLX_CORE_SOURCE_DIR}/include/flx"
        "${FLX_INSTALL_INCLUDE_DIR}"
    VERBATIM
)

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_CLEAN_FILES "${FLX_INSTALL_BASE_DIR}")