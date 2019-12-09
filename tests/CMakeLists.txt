cmake_minimum_required(VERSION 3.9)

### Set up googletest
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif ()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif ()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)
### END Set up googletest

### Find packages
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Include source
include_directories(${PROJECT_SOURCE_DIR}/src)

### Add/Make tests
add_executable(example_test example_test.cpp)
target_link_libraries(example_test gtest_main)
add_test(NAME example_test COMMAND example_test)

add_executable(vector_test vector_test.cpp ../src/shape_utils/vector.h)
target_link_libraries(vector_test gtest_main)
add_test(NAME vector_test COMMAND vector_test)

add_executable(polygon_test polygon_test.cpp 
    ../src/shape_utils/polygon.h
    ../src/shape_utils/polygon.cpp
    )
target_link_libraries(polygon_test gtest_main)
add_test(NAME polygon_test COMMAND polygon_test)
### END Add/Make tests
