cmake_minimum_required(VERSION 3.27)
project(project)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(main main.cpp)
add_executable(testing testing.cpp)
add_executable(testing2 testing2.cpp)

target_link_libraries(main OpenGL::GLU GLUT::GLUT)
target_link_libraries(testing2 OpenGL::GLU GLUT::GLUT)
target_link_libraries(testing OpenGL::GLU GLUT::GLUT)