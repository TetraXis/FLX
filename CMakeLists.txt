cmake_minimum_required(VERSION 3.31)
project(FLX LANGUAGES CXX)

set(FLX_INSTALL_BASE_DIR "${CMAKE_SOURCE_DIR}/INSTALL" CACHE PATH "Base installation directory for all FLX components")

add_subdirectory(CORE)
add_subdirectory(TEST/TEST_CORE)