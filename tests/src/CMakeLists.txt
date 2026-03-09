include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TEST_SOURCES *.cpp)


add_executable(QuestsTests ${TEST_SOURCES})

target_link_libraries(
        QuestsTests
        PRIVATE
        GTest::gtest
        gtest_main
        ${PROJECT_NAME}
)

target_include_directories(QuestsTests PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)