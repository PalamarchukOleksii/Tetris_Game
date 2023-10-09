cmake_minimum_required(VERSION 3.0.0)
project(CMakeTetris VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(SOURCES
Game_Tetris_Kursova/Desinge.cpp
Game_Tetris_Kursova/Designe.h
Game_Tetris_Kursova/Game.cpp
Game_Tetris_Kursova/Game.h
Game_Tetris_Kursova/resource.h
Game_Tetris_Kursova/Main.cpp
)

add_executable(CMakeTetris ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
