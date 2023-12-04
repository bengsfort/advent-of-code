cmake_minimum_required(VERSION 3.20)
project(day2)

# Compiler flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files + executable setup
set(SOURCES
	sources/main.cpp
)

add_executable(day2 ${SOURCES})

# Links
target_link_libraries(day2 PRIVATE utils)

# Configure target
set_target_properties(day2 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build
)

if(WIN32)
	target_compile_options(day2 PRIVATE -W4)
else()
	target_compile_options(day2 PRIVATE -Wall -Wextra -Wpedantic)
endif()




