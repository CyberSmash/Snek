cmake_minimum_required(VERSION 3.0)
project(snek)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
find_package(sdl2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

#include_directories(${SDL2_MIXER_INCLUDE_DIRS})
#find_package(SDL_MIXER REQUIRED)
add_executable(snek main.cpp GameObjects/GameObject.cpp GameObjects/GameObject.h defns.h GameObjects/Snake.cpp GameObjects/Snake.h Engine/InputRouter.cpp Engine/InputRouter.h GameObjects/Food.cpp GameObjects/Food.h Engine/Engine.cpp Engine/Engine.h Engine/Tag.h GameObjects/GameRunner.cpp GameObjects/GameRunner.h Engine/AudioEngine.cpp Engine/AudioEngine.h GameObjects/AudioController.cpp GameObjects/AudioController.h Engine/Scene.cpp Engine/Scene.h Scenes/MainGameScene.cpp Scenes/MainGameScene.h Scenes/TitleScreen.cpp Scenes/TitleScreen.h GameObjects/Logo.cpp GameObjects/Logo.h GameObjects/Utils.cpp GameObjects/Utils.h GameObjects/TitleScreenMenu.cpp GameObjects/TitleScreenMenu.h GameObjects/AISnake.cpp GameObjects/AISnake.h GameObjects/ScoreBoard.cpp GameObjects/ScoreBoard.h Scenes/OptionsScene.cpp Scenes/OptionsScene.h Engine/ui/UIMenu.cpp Engine/ui/UIMenu.h Engine/ui/MenuItem.cpp Engine/ui/MenuItem.h)
target_link_libraries(snek ncursesw ${SDL2_LIBRARIES} SDL2_mixer)