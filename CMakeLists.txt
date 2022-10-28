cmake_minimum_required(VERSION 3.0)

project(Library)

set(CMAKE_CXX_STANDARD 11)


set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)



add_subdirectory(tools)
add_subdirectory(sample)

