//
// Created by jordan on 5/21/19.
//

#include "Scene.h"

Scene::Scene(std::string sceneName) : name(std::move(sceneName))
{

}

std::string Scene::getName()
{
    return name;
}

std::list<std::shared_ptr<GameObject>> Scene::getGameObjects()
{
    return gameObjects;
}

void Scene::addGameObject(std::shared_ptr<GameObject> gameObject)
{
    gameObjects.emplace_back(gameObject);
}


void Scene::removeDestroyed()
{
    for (auto it = gameObjects.begin(); it != gameObjects.end();)
    {
        std::shared_ptr<GameObject> tmp = *it;
        if (tmp->isDestroyed())
        {
            it = gameObjects.erase(it);
            continue;
        }
        it++;
    }
}

void Scene::clearWindows()
{
    for (auto window : windows)
    {
        werase(window);
    }
}

void Scene::refreshWindows()
{
    for (auto window : windows)
    {
        wrefresh(window);
    }
}

void Scene::invalidateWindows()
{
    for (WINDOW* win : windows)
    {
        delwin(win);
    }
    windows.clear();
}

void Scene::UnloadScene()
{
    invalidateWindows();
}

Scene::~Scene()
{
    // Clean up anything that still needs cleaned up.
    if (!windows.empty())
    {
        invalidateWindows();
    }
}
