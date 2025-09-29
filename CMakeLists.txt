# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(SRI_Model)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the directory containing header files
include_directories(include)

# Add the main executable for the simulation
add_executable(sri_simulation src/main.cpp)

# Add the test executable
add_executable(run_tests src/test_sri.cpp)
