cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
project(map)

enable_testing()
add_subdirectory(tests)

add_executable(
        map
        main.cpp
        src/record.cpp
        src/shapefile.cpp
)
