cmake_minimum_required(VERSION 3.20)
project(cgproject)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)


add_executable(cgproject main.cpp)

target_link_libraries(cgproject PRIVATE
    GLUT::GLUT
    OpenGL::GL
)