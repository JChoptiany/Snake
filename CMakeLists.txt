cmake_minimum_required(VERSION 3.15)
project(Snake)

set(CMAKE_CXX_STANDARD 14)

include_directories(Include)

add_executable(Snake main.cpp Source/Board.cpp Source/Game.cpp)