cmake_minimum_required(VERSION 3.14)

project(ChessGame LANGUAGES C CXX)

# Add the subdirectories that contain our libraries.
# The 'pieces' library must be added before 'board' because 'board' depends on it.
add_subdirectory(core/pieces)
add_subdirectory(core/board)

add_executable(ChessGame)

target_sources(ChessGame
    PRIVATE
        main/main.cpp
)

target_link_libraries(ChessGame
    PRIVATE
        ChessBoard # ChessPieces is now a dependency of ChessBoard
)

target_compile_features(ChessGame PRIVATE cxx_std_23)
