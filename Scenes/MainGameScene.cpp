//
// Created by jordan on 5/21/19.
//

#include "MainGameScene.h"

MainGameScene::MainGameScene(std::string sceneName) : Scene(std::move(sceneName))
{
    windows.emplace_back(newwin(20, 40, 5, 5));
}

void MainGameScene::LoadScene()
{
    wclear(stdscr);
    wclear(windows[WINDOW_TAG::GAME_AREA]);
    gameObjects.emplace_back(std::make_shared<GameRunner>(windows[WINDOW_TAG::GAME_AREA]));
    gameObjects.emplace_back(std::make_shared<AISnake>(windows[WINDOW_TAG::GAME_AREA], 5, 5, 5, Direction::RIGHT));
    gameObjects.emplace_back(std::make_shared<AudioController>());
}

void MainGameScene::UnloadScene()
{
    gameObjects.clear();
}
