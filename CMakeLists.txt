cmake_minimum_required(VERSION 3.10)

# Set the project name
project(formatter)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(formatter main.cpp kern/kern.cpp)

# Include the kern directory to find the header files
target_include_directories(formatter PRIVATE ${CMAKE_SOURCE_DIR}/kern)

# Set the output directory for the executable
set_target_properties(formatter PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)