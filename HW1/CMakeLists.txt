cmake_minimum_required(VERSION 3.14)
project(HW1 C CXX)

add_library(hw1_lib STATIC
    src/checks.c
    src/classification.c
    src/comparison.c
    src/math.c
    src/representation.c
)
target_include_directories(hw1_lib PUBLIC include)
set_target_properties(hw1_lib PROPERTIES C_STANDARD 23)

add_executable(main main.c)
target_link_libraries(main PRIVATE hw1_lib)
set_target_properties(main PROPERTIES C_STANDARD 23)

enable_testing()
add_subdirectory(tests)
