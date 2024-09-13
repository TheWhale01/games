set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -g -lSDL2 -lSDL2main")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

cmake_minimum_required(VERSION 3.22.1)
project(pacman)
add_executable(pacman main.cpp)