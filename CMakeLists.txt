cmake_minimum_required(VERSION 3.14)
project(snek)

set(CMAKE_CXX_STANDARD 14)

add_executable(snek main.cpp GameObject.cpp GameObject.h defns.h Snake.cpp Snake.h InputRouter.cpp InputRouter.h Food.cpp Food.h Engine.cpp Engine.h)
target_link_libraries(snek ncursesw)