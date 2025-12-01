cmake_minimum_required(VERSION 4.0)
project(TEST)

set(CMAKE_CXX_STANDARD 23)

set(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/TEST/main.cpp")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})