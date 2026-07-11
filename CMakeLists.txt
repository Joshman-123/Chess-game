cmake_minimum_required(VERSION 3.14)

project(ChessGame LANGUAGES C CXX)

# Add the subdirectories that contain our libraries.
# The 'pieces' library must be added before 'board' because 'board' depends on it.
add_subdirectory(core/pieces)
add_subdirectory(core/board)
add_subdirectory(core/renderer/openGL)
add_subdirectory(core/utility)
add_subdirectory(core/render)

# --- GLFW Library Definition ---
# Create a target to represent the third-party GLFW library.
# This makes it easier and safer to link against.
add_library(glfw INTERFACE)


add_executable(ChessGame)

target_sources(ChessGame
    PRIVATE
        main/main.cpp
        third_party/glad/src/glad.c
)

target_include_directories(ChessGame
    PRIVATE
        third_party/glad/include
        third_party/
)
target_link_libraries(ChessGame
    PRIVATE
        OpenGLRender # Now linked correctly via the initializer function
        ChessBoard # This links ChessPieces, Render, and utility transitively
        "${CMAKE_SOURCE_DIR}/third_party/GLFW/lib/libglfw3.a"
)

target_compile_features(ChessGame PRIVATE cxx_std_23)
