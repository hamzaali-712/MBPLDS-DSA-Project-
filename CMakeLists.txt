cmake_minimum_required(VERSION 3.10)
project(MBPLDS)

set(CMAKE_CXX_STANDARD 17)

# Add all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Define the executable
add_executable(MBPLDS ${SOURCES})
