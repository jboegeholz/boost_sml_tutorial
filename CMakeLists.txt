cmake_minimum_required(VERSION 4.2)

project(boost_sml_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
include(CTest)

add_subdirectory(external/googletest)

add_executable(00_google_test
        tests/00_google_test.cpp
)

target_link_libraries(
        00_google_test
        PRIVATE
        GTest::gtest_main
        gmock
)

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

add_executable(05_sm_with_guards_test
        tests/05_sm_with_guards_test.cpp
)

target_link_libraries(
        05_sm_with_guards_test
        PRIVATE
        GTest::gtest_main
)

add_executable(06_sm_with_guard_functors_test
        tests/06_sm_with_guard_and_di_test.cpp
)

target_link_libraries(
        06_sm_with_guard_functors_test
        PRIVATE
        GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(00_google_test)
gtest_discover_tests(01_simple_state_machine_test)
gtest_discover_tests(02_sm_with_actions_test)
gtest_discover_tests(05_sm_with_guards_test)
gtest_discover_tests(06_sm_with_guard_functors_test)