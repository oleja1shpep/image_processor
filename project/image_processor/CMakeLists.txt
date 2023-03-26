cmake_minimum_required(VERSION 3.25)

project(image_processor)

set(CMAKE_CXX_STANDARD 23)

add_executable(
        image_processor
        image_processor.cpp
)

add_subdirectory(image)
add_subdirectory(filters)
add_subdirectory(file_worker)
add_subdirectory(unit_tests)

target_link_libraries(image_processor image filters file_worker)
