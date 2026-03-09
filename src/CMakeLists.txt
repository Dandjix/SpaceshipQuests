

file(GLOB_RECURSE LIB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

message(STATUS "Sources found: ${LIB_SOURCES}")

add_library(${PROJECT_NAME} ${LIB_SOURCES})