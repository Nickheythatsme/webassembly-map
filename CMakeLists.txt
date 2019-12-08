cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(map)

enable_testing()
add_subdirectory(tests)


# Download and Build GLEW
SET(GLEW_VERSION glew-2.1.0)
SET(GLEW_filename ${CMAKE_CURRENT_BINARY_DIR}/${GLEW_VERSION}.tar.gz)
SET(GLEW_outdir ${CMAKE_CURRENT_BINARY_DIR}/${GLEW_VERSION})
SET(URL https://ayera.dl.sourceforge.net/project/glew/glew/2.1.0/${GLEW_VERSION}.tgz)

if (NOT EXISTS ${GLEW_outdir})
    if (NOT EXISTS ${GLEW_filename})
        file(DOWNLOAD ${URL} ${GLEW_filename}
           TIMEOUT 60  # seconds
           SHOW_PROGRESS
          )
    endif()
else()
    message(STATUS "Skipping download of GLEW as ${GLEW_outdir} already exists")
endif()
if (NOT EXISTS ${GLEW_outdir}/build/glew.rc)
    execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xf ${GLEW_filename}
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    execute_process(COMMAND ${CMAKE_COMMAND} -E time make 
        WORKING_DIRECTORY ${GLEW_outdir})
else()
    message(STATUS "Skipping building GLEW as build/glew.rc file already exists")
endif()

SET(FREEGLUT_VERSION freeglut-3.2.1)
SET(FREEGLUT_filename ${CMAKE_CURRENT_BINARY_DIR}/${FREEGLUT_VERSION}.tar.gz)
SET(FREEGLUT_outdir ${CMAKE_CURRENT_BINARY_DIR}/${FREEGLUT_VERSION})
SET(URL https://svwh.dl.sourceforge.net/project/freeglut/freeglut/3.2.1/${FREEGLUT_VERSION}.tar.gz)

if (NOT EXISTS ${FREEGLUT_outdir})
    if (NOT EXISTS ${FREEGLUT_filename})
        file(DOWNLOAD ${URL} ${FREEGLUT_filename}
           TIMEOUT 60  # seconds
           SHOW_PROGRESS
          )
    endif()
else()
    message(STATUS "Skipping download of FREEGLUT as ${FREEGLUT_outdir} already exists")
endif()
if (NOT EXISTS ${FREEGLUT_outdir}/build/glew.rc)
    execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xf ${FREEGLUT_filename}
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
else()
    message(STATUS "Skipping building FREEGLUT as build/glew.rc file already exists")
endif()

find_package(OpenGL)
find_package(GLUT)
find_package(SDL2)

if (${OPENGL_FOUND})
    set(GLEW_INCLUDE_DIRS ${GLEW_outdir}/include)
    set(GLEW_LIBRARIES ${GLEW_outdir}/lib/libGLEW.a)
    include_directories(${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
    add_executable(glut_fullscreen
        glut_fullscreen.cpp
    )
    target_link_libraries(glut_fullscreen 
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLUT_LIBRARY}
        )
endif()
SET(SDL2_VERSION SDL2-2.0.10)
SET(SDL2_filename ${CMAKE_CURRENT_BINARY_DIR}/${SDL2_VERSION}.tar.gz)
SET(SDL2_outdir ${CMAKE_CURRENT_BINARY_DIR}/${SDL2_VERSION})
SET(URL https://www.libsdl.org/release/${SDL2_VERSION}.tar.gz)

if (NOT EXISTS ${SDL2_outdir})
    if (NOT EXISTS ${SDL2_filename})
        file(DOWNLOAD ${URL} ${SDL2_filename}
           TIMEOUT 60  # seconds
           SHOW_PROGRESS
          )
    endif()
    execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xf ${SDL2_filename}
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    if (NOT EXISTS ${SDL2_outdir}/build/SDL.o)
        execute_process(COMMAND ${CMAKE_COMMAND} -E time ./configure
            WORKING_DIRECTORY ${SDL2_outdir})
        execute_process(COMMAND ${CMAKE_COMMAND} -E time make
            WORKING_DIRECTORY ${SDL2_outdir})
    endif()
endif()

if (${OPENGL_FOUND} AND ${SDL2_FOUND})
    set(SDL2_INCLUDE_DIR ${SDL2_outdir}/include)
    include_directories(${OPENGL_INCLUDE_DIR} ${SDL2_INCLUDE_DIR})
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
