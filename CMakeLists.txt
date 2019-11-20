cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)
project(map)

enable_testing()
add_subdirectory(tests)

find_package(SDL REQUIRED)
include_directories(${SDL_INCLUDE_DIR})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
message(${GLEW_INCLUDE_DIRS})

add_executable(
        map
        main.cpp
        src/record.cpp
        src/shapefile.cpp
)

add_executable(
        sdl
        sdl_example.cpp
)
target_link_libraries(sdl ${SDL_LIBRARY} ${GLEW_LIBRARIES})

