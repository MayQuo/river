# river-sandbox
# license: MIT 
# project setup
cmake_minimum_required(VERSION 3.17)
project(river-sandbox VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MAKE_PROGRAM make)
set(CMAKE_BUILD_TYPE release)

# linking shared library
set(PROJECT_LINK_LIBS libriver.so)
link_directories(../river-framework/build-linux)


# include
include_directories(src/)
include_directories(../river-framework/src/)

# collect source files
file(GLOB_RECURSE SOURCES src/*.cpp)

# generate executable
add_executable(sandbox ${SOURCES})
target_link_libraries(sandbox ${PROJECT_LINK_LIBS})