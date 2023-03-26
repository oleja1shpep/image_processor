set(CMAKE_CXX_STANDARD 20)

cmake_minimum_required(VERSION 3.24)

project(image_processor)

set(CMAKE_MODULE_PATH              "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

set(CXX_STANDARD_REQUIRED ON)


message("C++ version: ${CMAKE_CXX_STANDARD}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wimplicit-fallthrough -g")

set(CMAKE_CXX_FLAGS_ASAN "-g -fsanitize=address,undefined -fno-sanitize-recover=all"
    CACHE STRING "Compiler flags in asan build"
    FORCE)

set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_ASAN} -fprofile-instr-generate -fcoverage-mapping")


include_directories(util)

# project
add_subdirectory(project/image_processor)
