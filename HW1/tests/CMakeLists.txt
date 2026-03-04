include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

function(add_hw1_test target source)
    add_executable(${target} ${source})
    target_link_libraries(${target} PRIVATE hw1_lib GTest::gtest_main)
    set_target_properties(${target} PROPERTIES CXX_STANDARD 17)
    add_test(NAME ${target} COMMAND ${target})
endfunction()

add_hw1_test(test_checks       test_checks.cpp)
add_hw1_test(test_classification test_classification.cpp)
add_hw1_test(test_comparison   test_comparison.cpp)
add_hw1_test(test_math         test_math.cpp)
add_hw1_test(test_representation test_representation.cpp)
