cmake_minimum_required(VERSION 3.20)
project(day1)

# Compiler flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files + executable setup
set(SOURCES
	sources/main.cpp
)

add_executable(day1 ${SOURCES})

# Links
target_link_libraries(day1 PRIVATE utils)

# Copy inputs
file(COPY inputs DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/build)

# Configure target
set_target_properties(day1 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build
)

if(WIN32)
	target_compile_options(day1 PRIVATE -W4)
else()
	target_compile_options(day1 PRIVATE -Wall -Wextra -Wpedantic)
endif()




