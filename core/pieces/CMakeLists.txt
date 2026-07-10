cmake_minimum_required(VERSION 3.14)

# It's good practice for sub-projects not to have their own project() call
# if they are part of a larger project. The top-level CMakeLists.txt
# should contain the project() call.

# This creates a library named "ChessPieces".
# Your main executable can then link against this library.

# Automatically find all .cpp files in this directory and its subdirectories.
# CONFIGURE_DEPENDS ensures that if you add/remove a file, CMake will re-run.
file(GLOB_RECURSE PIECE_SOURCES CONFIGURE_DEPENDS "*.cpp")
add_library(ChessPieces ${PIECE_SOURCES})

# This makes the "include" directory available for compilation within this library.
# By marking it PUBLIC, we export it to any other target that links against ChessPieces.
# This allows your main.cpp to do #include <Piece.h> without any extra configuration.
target_include_directories(ChessPieces
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/includes # Public headers are in the 'src' directory
)

target_compile_features(ChessPieces PRIVATE cxx_std_23)
