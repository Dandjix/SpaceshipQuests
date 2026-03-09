cmake_minimum_required(VERSION 4.0)
project(Quests LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 26)

include(FetchContent)

add_subdirectory(src)


option(BUILD_TESTS "Build tests")
if(BUILD_TESTS)
    add_subdirectory(tests/src)
endif()