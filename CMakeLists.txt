cmake_minimum_required(VERSION 3.17)

# define values
set ( PROJECT_NAME river)               # project name
set ( EXTERN_LIB_PATH "../Lib/")        # path to extern libaries
set ( PROJECT_VERSION 1.0)              # project version
set ( CMAKE_CXX_STANDARD 17)            # c++ version
set ( CMAKE_MAKE_PROGRAM make)          # make program

project(${PROJECT_NAME} VERSION ${PROJECT_VERSION}) # setup project

# find_package(Freetype REQUIRED)

# linking system dependencies
if (UNIX)
    set ( CMAKE_CXX_FLAGS " -lGL -lX11 -lpthread -lXrandr -lXi -ldl")
endif()

# TODO WIN32: MINGW MSVC / APPLE: CLANG


# linking directory:
if (UNIX)
    set ( PROJECT_LINK_LIBS "-lglfw3")
    link_directories( ${EXTERN_LIB_PATH}glfw/build/src)
    link_directories( ${EXTERN_LIB_PATH}freetype-2/build/)
endif()

# include directory:
include_directories( src/ )
include_directories( ${EXTERN_LIB_PATH}glfw/include/)
include_directories( ${EXTERN_LIB_PATH}glad/include/)
include_directories( ${EXTERN_LIB_PATH}glm/)
# include_directories( ${EXTERN_LIB_PATH}freetype-2/include/)

# append files
file ( GLOB SOURCES "src/*.cpp")
file ( GLOB SOURCES2 "src/app/*.cpp")
file ( GLOB SOURCES3 "src/render/*.cpp")

add_executable(${PROJECT_NAME} "src/glad.c" ${SOURCES} ${SOURCES2} ${SOURCES3})
target_link_libraries(${PROJECT_NAME} ${PROJECT_LINK_LIBS})
# target_link_libraries(${PROJECT_NAME} ${FREETYPE_LIBRARIES})
# target_include_directories(${PROJECT_NAME} PRIVATE ${FREETYPE_INCLUDE_DIRS})
