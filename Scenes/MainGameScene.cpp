//
// Created by jordan on 5/21/19.
//

#include "MainGameScene.h"
#define SCREEN_TOTAL_X 80
#define SCREEN_TOTAL_Y 40
MainGameScene::MainGameScene(std::string sceneName) : Scene(std::move(sceneName))
{

    int start_draw_x = (getmaxx(stdscr) / 2) - (SCREEN_TOTAL_X / 2);
    int start_draw_y = (getmaxy(stdscr) / 2) - (SCREEN_TOTAL_Y / 2);
    windows.emplace_back(newwin(40, 80, start_draw_y, start_draw_x));
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
