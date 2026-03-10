file(GLOB_RECURSE LIB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(${PROJECT_NAME} ${LIB_SOURCES})

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)

# Install the library binary
install(TARGETS ${PROJECT_NAME}
        EXPORT QuestsTargets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

# Install headers
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/
        DESTINATION include
        FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)

# Export the targets
install(EXPORT QuestsTargets
        FILE QuestsConfig.cmake
        NAMESPACE Quests::
        DESTINATION lib/cmake/Quests
)