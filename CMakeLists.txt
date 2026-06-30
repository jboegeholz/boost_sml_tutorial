cmake_minimum_required(VERSION 4.2)

project(boost_sml_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include(CTest)

add_subdirectory(external/googletest)

add_executable(01_simple_state_machine_test
        tests/01_simple_state_machine_test.cpp
)

target_link_libraries(
        01_simple_state_machine_test
        PRIVATE
        GTest::gtest_main
)

add_executable(02_sm_with_actions_test
        tests/02_sm_with_actions_test.cpp
)

target_link_libraries(
        02_sm_with_actions_test
        PRIVATE
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(01_simple_state_machine_test)
gtest_discover_tests(02_sm_with_actions_test)