cmake_minimum_required(VERSION 3.5)
project(Tetris)

add_library(MyLib 
Game_Tetris_Kursova/designe.cpp 
Game_Tetris_Kursova/designe.h 
Game_Tetris_Kursova/game.cpp 
Game_Tetris_Kursova/game.h
)

add_executable(MyTetris Game_Tetris_Kursova/main.cpp)

target_link_libraries(MyTetris PUBLIC MyLib)