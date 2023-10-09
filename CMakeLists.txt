cmake_minimum_required(VERSION 3.0.0)
project(CMakeTetris VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(CMakeTetris Main.cpp)

set(SOURCES
src/Desinge.cpp
src/Designe.h
src/Game.cpp
src/Game.h
src/resource.h
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
