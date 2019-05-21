//
// Created by jordan on 5/21/19.
//

#include "Scene.h"

Scene::Scene(std::string sceneName) : name(sceneName)
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
