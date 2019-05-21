//
// Created by jordan on 5/21/19.
//

#include "MainGameScene.h"

MainGameScene::MainGameScene(std::string sceneName) : Scene(std::move(sceneName))
{

}

void MainGameScene::LoadScene(WINDOW *win)
{
    gameObjects.emplace_back(std::make_shared<GameRunner>(win));
    gameObjects.emplace_back(std::make_shared<Snake>(win, 5, 5, 5, Direction::RIGHT));
    gameObjects.emplace_back(std::make_shared<AudioController>());
}

void MainGameScene::UnloadScene()
{
    gameObjects.clear();
}
