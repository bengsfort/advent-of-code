cmake_minimum_required(VERSION 3.20)
project(day5)

# Compiler flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files + executable setup
set(SOURCES
	sources/main.cpp
	sources/debug.h
	sources/parsing.h
	sources/parsing.cpp
	sources/solver.h
	sources/part1solver.h
	sources/part1solver.cpp
	sources/part2solver.h
	sources/part2solver.cpp
)

add_subdirectory(../utils ${CMAKE_CURRENT_BINARY_DIR}/build/utils)
add_executable(day5 ${SOURCES})

# Links
target_link_libraries(day5 PRIVATE utils)

# Configure target
set_target_properties(day5 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build
)

if(WIN32)
	target_compile_options(day5 PRIVATE -W4)
else()
	target_compile_options(day5 PRIVATE -Wall -Wextra -Wpedantic)
endif()




