cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(map)

enable_testing()
add_subdirectory(tests)

find_package(SDL)
if (${SDL_FOUND})
    message(STATUS "Found SDL")
endif()

find_package(GLEW)
if (${GLEW_FOUND})
    message(STATUS "Found GLEW")
endif()

if (${GLEW_FOUND} AND ${SDL_FOUND})
    include_directories(${GLEW_INCLUDE_DIRS})
    include_directories(${SDL_INCLUDE_DIR})
    add_executable(
            sdl
            sdl_example.cpp
    )
    target_link_libraries(sdl ${SDL_LIBRARY} ${GLEW_LIBRARIES})
endif()

add_executable(
        map
        main.cpp
        src/record.cpp
        src/shapefile.cpp
        src/shape_utils.cpp
)


