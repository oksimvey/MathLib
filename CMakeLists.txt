cmake_minimum_required(VERSION 3.16)

project(MathLib)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)

add_executable(MathLib ${SRC_FILES})