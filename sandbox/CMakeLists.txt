cmake_minimum_required(VERSION 3.17)
project(river-sandbox VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(SOURCES
    ${SRC_DIR}/main.cpp
)

set(PROJECT_LINK_LIBS 
    libriver.so
)
link_directories(../framework/build)

add_executable(sandbox ${SOURCES})
target_link_libraries(sandbox ${PROJECT_LINK_LIBS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../framework/include)