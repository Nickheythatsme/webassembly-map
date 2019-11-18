cmake_minimum_required(VERSION 3.14)
project(map)

set(CMAKE_CXX_STANDARD 17)

set(SRC src/shapefile.cpp)
add_executable(map main.cpp)

