cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(map)

enable_testing()
add_subdirectory(tests)

#find_package(OpenGL)
#find_package(SDL2)

if (${OPENGL_FOUND} AND ${SDL2_FOUND})
    #set(SDL2_INCLUDE_DIRS ${SDL2_outdir}/include)
    message(${SDL2_INCLUDE_DIRS})
    include_directories(${OPENGL_INCLUDE_DIR} ${SDL2_INCLUDE_DIRS})
    add_executable(
        sdl2
        sdl2_canvas_write.cpp
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
