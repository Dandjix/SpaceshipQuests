cmake_minimum_required(VERSION 4.0)
project(Quests LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 26)

include(FetchContent)

add_subdirectory(quests)


option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()