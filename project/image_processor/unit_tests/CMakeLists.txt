project(unit_tests)

set(CMAKE_CXX_STANDARD 23)

add_executable(
        unit_tests
        test.cpp
)

target_link_libraries(unit_tests image filters file_worker)
