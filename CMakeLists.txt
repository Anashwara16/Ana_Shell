cmake_minimum_required(VERSION 3.20)
project(anashell VERSION 0.1.0 LANGUAGES CXX)

# Use C++20 (or bump to C++23 later)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Include directories
include_directories(include)

# Source files for now — just main.cpp and repl
set(SOURCES
    src/main.cpp
    src/repl.cpp
)

# Headers (optional for now)
set(HEADERS
    include/repl.h
)

# Define main shell executable
add_executable(anashell ${SOURCES} ${HEADERS})
