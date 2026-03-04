cmake_minimum_required(VERSION 3.14)

project(ChessGame LANGUAGES C CXX)

add_executable(ChessGame)

target_sources(ChessGame
    PRIVATE
        main/main.cpp
)

target_compile_features(ChessGame PRIVATE cxx_std_23)
