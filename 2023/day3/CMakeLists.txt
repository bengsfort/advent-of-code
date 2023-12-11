cmake_minimum_required(VERSION 3.20)
project(day3)

# Compiler flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files + executable setup
set(SOURCES
	sources/main.cpp
)

add_subdirectory(../utils ${CMAKE_CURRENT_BINARY_DIR}/build/utils)
add_executable(day3 ${SOURCES})

# Links
target_link_libraries(day3 PRIVATE utils)

# Configure target
set_target_properties(day3 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build
)

if(WIN32)
	target_compile_options(day3 PRIVATE -W4)
else()
	target_compile_options(day3 PRIVATE -Wall -Wextra -Wpedantic)
endif()




