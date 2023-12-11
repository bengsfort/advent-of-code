cmake_minimum_required(VERSION 3.20)

project(utils)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(UTILS_SOURCES
	sources/utilities.cpp
)

add_library(utils ${UTILS_SOURCES})

target_include_directories(utils
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)
