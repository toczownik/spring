cmake_minimum_required(VERSION 3.17)
project(spring)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE DEBUG)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLUT REQUIRED)

add_executable(spring main.cpp)

add_dependencies(spring OpenGL::OpenGL)
include_directories(${GLUT_INCLUDE_DIRS})

target_link_libraries(spring OpenGL::OpenGL ${GLUT_LIBRARY})
target_link_libraries(spring GLU)
target_link_libraries(spring GL)