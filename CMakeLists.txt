cmake_minimum_required(VERSION 3.10)
project(RROS)
set(CMAKE_C_STANDARD 11)
set(BUILD_WITH_TESTS True CACHE STRING "Build with tests")
add_subdirectory(3rd_party)
add_subdirectory(src)
if( BUILD_WITH_TESTS )
    add_subdirectory(test)
endif()


