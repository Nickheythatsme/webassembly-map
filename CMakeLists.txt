cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(map)

enable_testing()
add_subdirectory(tests)


# Download and Build SDL2
SET(SDL2_VERSION SDL2-2.0.10)
SET(SDL2_filename ${CMAKE_CURRENT_BINARY_DIR}/${SDL2_VERSION}.tar.gz)
SET(SDL2_outdir ${CMAKE_CURRENT_BINARY_DIR}/${SDL2_VERSION})
SET(URL https://www.libsdl.org/release/${SDL2_VERSION}.tar.gz)

#if (NOT EXISTS ${SDL2_outdir})
#    if (NOT EXISTS ${SDL2_filename})
#        file(DOWNLOAD ${URL} ${SDL2_filename}
#           TIMEOUT 60  # seconds
#           SHOW_PROGRESS
#          )
#    endif()
#    execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xf ${SDL2_filename}
#                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
#    if (NOT EXISTS ${SDL2_outdir}/build/SDL.o)
#        execute_process(COMMAND ${CMAKE_COMMAND} -E time ./configure
#            WORKING_DIRECTORY ${SDL2_outdir})
#        execute_process(COMMAND ${CMAKE_COMMAND} -E time make 
#            WORKING_DIRECTORY ${SDL2_outdir})
#    endif()
#endif()

find_package(OpenGL)
find_package(SDL2)

if (${OPENGL_FOUND} AND ${SDL2_FOUND})
    include_directories(${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})
    add_executable(
            sdl2
            sdl2_example.cpp
    )
    target_link_libraries(sdl2 
        ${OPENGL_LIBRARIES}
        ${SDL2_LIBRARIES}
        )
endif()

add_executable(
        map
        main.cpp
        src/record.cpp
        src/shapefile.cpp
        src/shape_utils/vector.h
        src/shape_utils/line.h
)

add_test(NAME map COMMAND map ${CMAKE_SOURCE_DIR}/data/Neighborhoods_Regions.shp)
