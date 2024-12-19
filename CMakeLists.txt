cmake_minimum_required(VERSION 3.10)

# Set the project name
project(formatter)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT (CMAKE_SYSTEM_NAME STREQUAL "Darwin"))
	message(STATUS "STATIC LINKING: Setting GNU GCC/G++ parameters.")
	set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
	message(VERBOSE "CMAKE_FIND_LIBRARY_SUFFIXES: .a")
	set(BUILD_SHARED_LIBS OFF)
	message(VERBOSE "BUILD_SHARED_LIBS: OFF")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
	message(VERBOSE "CMAKE_EXE_LINKER_FLAGS: -static")
else()
	message(STATUS "STATIC LINKING: Darwin detected; not statically linking.")
endif()

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")

# Add the executable
add_executable(formatter main.cpp utils.cpp kern/kern.cpp)

# Include the kern directory to find the header files
target_include_directories(formatter PRIVATE ${CMAKE_SOURCE_DIR}/kern)

# Set the output directory for the executable
set_target_properties(formatter PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)