include(GoogleTest)
set(TESTS_PROJECT RROS_Tests)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_executable(RROS_Tests UT_RROS.cpp mock/mock.cpp)
target_include_directories(RROS_Tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/mock)

target_link_libraries(RROS_Tests PUBLIC RROS_lib gtest gtest_main gmock)
gtest_add_tests(TARGET RROS_Tests
                TEST_SUFFIX .noArgs
                TEST_LIST noArgsTests)
