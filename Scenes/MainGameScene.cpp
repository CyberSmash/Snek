/**
 * The scene of the main game screen.
 */


#include "MainGameScene.h"
#define SCREEN_TOTAL_X 80
#define SCREEN_TOTAL_Y 40
MainGameScene::MainGameScene(std::string sceneName) : Scene(std::move(sceneName))
{


}

void MainGameScene::LoadScene()
{
    int start_draw_x = (getmaxx(stdscr) / 2) - (SCREEN_TOTAL_X / 2);
    int start_draw_y = (getmaxy(stdscr) / 2) - (SCREEN_TOTAL_Y / 2);
    windows.emplace_back(newwin(40, 80, start_draw_y, start_draw_x));
    windows.emplace_back(newwin(3, 80, start_draw_y - 3, start_draw_x));
    wclear(stdscr);
    wclear(windows[WINDOW_TAG::GAME_AREA]);
    gameObjects.emplace_back(std::make_shared<GameRunner>(windows[WINDOW_TAG::GAME_AREA]));
    gameObjects.emplace_back(std::make_shared<Snake>(windows[WINDOW_TAG::GAME_AREA], 5, 5, 5, Direction::RIGHT));
    gameObjects.emplace_back(std::make_shared<AudioController>());
    gameObjects.emplace_back(std::make_shared<ScoreBoard>(windows[WINDOW_TAG::SCORE_BOARD], 1, 1));
}

void MainGameScene::UnloadScene()
{
    gameObjects.clear();
}
