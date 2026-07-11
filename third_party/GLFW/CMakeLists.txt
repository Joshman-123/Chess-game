add_library(glfw INTERFACE)

target_include_directories(glfw
    INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}/.."
)

target_link_libraries(glfw INTERFACE glfw3)
