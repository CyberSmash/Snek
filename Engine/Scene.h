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
    virtual void                LoadScene()     = 0;
    virtual void                UnloadScene()   = 0;
    std::list<GameObjectSptr>   getGameObjects();
    void                        addGameObject(GameObjectSptr gameObject);
    void                        removeDestroyed();
    std::string                 getName();
    void                        clearWindows();
    void                        refreshWindows();
    void                        invalidateWindows();
    virtual                     ~Scene();

protected:
    std::list<GameObjectSptr>       gameObjects;
    std::string                     name;
    std::vector<WINDOW*>            windows;

};


#endif //SNEK_SCENE_H
