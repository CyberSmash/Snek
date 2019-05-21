//
// Created by jordan on 5/21/19.
//

#ifndef SNEK_SCENE_H
#define SNEK_SCENE_H

#include <string>
#include <list>
#include <memory>
#include <curses.h>
#include "GameObjects/GameObject.h"

class Scene
{
public:
    Scene(std::string sceneName);
    virtual void LoadScene(WINDOW* window) = 0;
    virtual void UnloadScene() = 0;
    std::list<std::shared_ptr<GameObject>> getGameObjects();
    std::string getName();

protected:
    std::list<std::shared_ptr<GameObject>> gameObjects;
    std::string name;

};


#endif //SNEK_SCENE_H
