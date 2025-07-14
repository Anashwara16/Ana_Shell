cmake_minimum_required(VERSION 3.20)
project(anashell VERSION 0.1.0 LANGUAGES CXX)

# Use modern C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Add include directory
include_directories(include)

# Define executable target with sources
add_executable(anashell
    src/main.cpp
    src/shell.cpp
)

# Optional: make headers visible to IDE (but not needed for build)
target_sources(anashell PRIVATE
    include/shell.hpp
)