cmake_minimum_required(VERSION 3.27)
project(project)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(main main.cpp
        ui_components/cuboid/cuboid.cpp
        ui_components/cuboid/cuboid.h
        ui_components/house/house.cpp
        ui_components/house/house.h
        colors/colors.cpp
        colors/colors.h)

target_link_libraries(main OpenGL::GLU GLUT::GLUT)
