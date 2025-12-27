cmake_minimum_required (VERSION 3.10)
project("registry")

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/bin")
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

add_subdirectory("src")