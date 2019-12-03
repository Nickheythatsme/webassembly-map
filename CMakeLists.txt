cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(map)

enable_testing()
add_subdirectory(tests)

find_package(SDL2)
find_package(OpenGL)

if (${SDL2_FOUND} AND ${OPENGL_FOUND})
    include_directories(${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})
    add_executable(
            sdl2
            sdl2_example.cpp
    )
    target_link_libraries(sdl2 ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
endif()

add_executable(
        map
        main.cpp
        src/record.cpp
        src/shapefile.cpp
        src/shape_utils/vector.h
        src/shape_utils/line.h
)
