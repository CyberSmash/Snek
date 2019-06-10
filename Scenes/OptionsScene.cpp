/**
 * Options Scene for setting user-defined options.
 */

#include <ncurses.h>
#include "GameObjects/Options/OptionsMenu.h"
#include "GameObjects/Utils.h"
#include "OptionsScene.h"


OptionsScene::OptionsScene(std::string sceneName) : Scene(std::move(sceneName))
{

}

void OptionsScene::LoadScene()
{
    int xPos = (getmaxx(stdscr) / 2) - (80 / 2);
    int yPos = (getmaxy(stdscr) / 2) - (40 / 2);
    windows.emplace_back(newwin(40, 80, yPos, xPos));
    gameObjects.emplace_back(std::make_shared<OptionsMenu>(windows[WINDOW_TAG::OPTIONS_MENU], 0, 0));

    wclear(stdscr);
    wclear(windows[WINDOW_TAG::OPTIONS_MENU]);
}

void OptionsScene::UnloadScene()
{
    Scene::UnloadScene();
    gameObjects.clear();
}
