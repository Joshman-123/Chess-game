cmake_minimum_required(VERSION 3.14)

# It's good practice for sub-projects not to have their own project() call
# if they are part of a larger project. The top-level CMakeLists.txt
# should contain the project() call.

# This creates a library named "ChessBoard".
# Your main executable can then link against this library.

# Automatically find all .cpp files in this directory and its subdirectories.
file(GLOB_RECURSE BOARD_SOURCES CONFIGURE_DEPENDS "*.cpp")
add_library(ChessBoard ${BOARD_SOURCES})

# This makes the "include" directory available for compilation within this library.
target_include_directories(ChessBoard
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/includes # Public headers are in the 'src' directory
)
target_link_libraries(ChessBoard PUBLIC utility Render)
# This command is crucial. It does two things:
# 1. PUBLIC Include Directories: Any target that links to ChessBoard will automatically
#    get its 'include' directory added to their include paths.
# 2. PUBLIC Linking: Any target that links to ChessBoard will also be linked to ChessPieces.
target_link_libraries(ChessBoard PUBLIC ChessPieces)

target_compile_features(ChessBoard PRIVATE cxx_std_23)
