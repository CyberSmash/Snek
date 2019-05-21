cmake_minimum_required(VERSION 3.14)
project(snek)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long")

find_package(sdl2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

include_directories(${SDL2_MIXER_INCLUDE_DIRS})
#find_package(SDL_MIXER REQUIRED)
add_executable(snek main.cpp GameObject.cpp GameObject.h defns.h Snake.cpp Snake.h InputRouter.cpp InputRouter.h Food.cpp Food.h Engine.cpp Engine.h Tag.h EngineUtils.cpp EngineUtils.h GameRunner.cpp GameRunner.h AudioEngine.cpp AudioEngine.h AudioController.cpp AudioController.h)
target_link_libraries(snek ncursesw ${SDL2_LIBRARIES} SDL2_mixer)