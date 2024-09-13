set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -g")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# file(GLOB SOURCES "src/*.cpp")

cmake_minimum_required(VERSION 3.22.1)
project(pacman)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# CA MARCHE PAS !
# add_executable(pacman ${SOURCES})
add_executable(pacman src/main.cpp src/Game.cpp)
target_include_directories(pacman PUBLIC includes)
target_link_libraries(pacman SDL2::SDL2)