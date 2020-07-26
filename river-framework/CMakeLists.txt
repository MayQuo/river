# river-framework
# license: MIT 
# project setup
cmake_minimum_required(VERSION 3.17)
project(river-framework VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MAKE_PROGRAM make)
set(CMAKE_BUILD_TYPE release)

# include
include_directories(src/)
include_directories(third-party/glfw/include/)
include_directories(third-party/freetype2/include/)
include_directories(third-party/glad/include/)
include_directories(third-party/stb/)

# collect source files
file(GLOB_RECURSE EXTERN_SOURCES third-party/*.cpp)
file(GLOB_RECURSE SOURCES src/*.cpp)

# generate shared library
add_library(river SHARED ${EXTERN_SOURCES} ${SOURCES})
