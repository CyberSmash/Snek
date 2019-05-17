cmake_minimum_required(VERSION 3.14)
project(snek)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long")
add_executable(snek main.cpp GameObject.cpp GameObject.h defns.h Snake.cpp Snake.h InputRouter.cpp InputRouter.h Food.cpp Food.h Engine.cpp Engine.h Tag.h EngineUtils.cpp EngineUtils.h)
target_link_libraries(snek ncursesw)