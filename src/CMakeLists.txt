cmake_minimum_required(VERSION 3.13)
project(KEPLER)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wextra -O3 -Wpedantic -Wunused -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -O3 -Wshadow -Wpedantic -Wold-style-cast -Wcast-align -Wunused -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches")

add_executable(${PROJECT_NAME} main.cpp
                               celestialObject.cpp
                               earth.cpp
                               exomoon.cpp
                               exoplanet.cpp
                               fileio.cpp
                               functions.cpp
                               jupiter.cpp
                               star.cpp
                               sun.cpp
                               timedisc.cpp)

set(EXECUTABLE_OUTPUT_PATH ..)
