include(GoogleTest)
set(TESTS_PROJECT RROS_Tests)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_executable(RROS_Tests UT_RROS.cpp)
gtest_add_tests(TARGET RROS_Tests
                TEST_SUFFIX .noArgs
                TEST_LIST noArgsTests)
target_link_libraries(RROS_Tests PUBLIC RROS_lib gtest gtest_main )
