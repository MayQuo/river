cmake_minimum_required(VERSION 3.17)
project(river-framework-project VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third-party)

# add sources here 
set(SOURCES
    ${LIB_DIR}/glad/src/glad.c
    ${SRC_DIR}/river.cpp
    ${SRC_DIR}/app/application.cpp
    ${SRC_DIR}/core/rmath.cpp
    ${SRC_DIR}/app/asset_manager.cpp
    ${SRC_DIR}/render/shader.cpp
)

add_library(river SHARED ${SOURCES})
target_include_directories(river
    PRIVATE
        ${SRC_DIR}
)

# setup OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# setup GLFW
set(GLFW_DIR ${LIB_DIR}/glfw)
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory(${GLFW_DIR})
target_link_libraries(river glfw ${GLFW_LIBRARIES})
target_include_directories(river PUBLIC ${GLFW_DIR}/include)
target_compile_definitions(river PUBLIC GLFW_INCLUDE_NONE)

# setup GLM
include_directories(${LIB_DIR}/glm)

# setup freetype
find_package(Freetype REQUIRED)

target_include_directories(river PUBLIC ${FREETYPE_INCLUDE_DIR})
target_link_libraries(river ${FREETYPE_LIBRARIES})

# include third-party directories
include_directories(${LIB_DIR}/glfw/include)
include_directories(${LIB_DIR}/glad/include)