cmake_minimum_required(VERSION 3.10)

# Set the project name
project(formatter)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(CMAKE_CXX_COMPILER_ID EQUAL "MSVC")
	set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
	target_compile_options(formatter [PUBLIC|PRIVATE] /MT)
	target_link_options(formatter [PUBLIC|PRIVATE] /INCREMENTAL:NO /NODEFAULTLIB:MSVCRT)
else()
	set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
	set(BUILD_SHARED_LIBS OFF)
	set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

# Add the executable
add_executable(formatter main.cpp kern/kern.cpp)

# Include the kern directory to find the header files
target_include_directories(formatter PRIVATE ${CMAKE_SOURCE_DIR}/kern)

# Set the output directory for the executable
set_target_properties(formatter PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)