//
// Created by jordan on 5/8/19.
//

#ifndef SNEK_GAMEOBJECT_H
#define SNEK_GAMEOBJECT_H

#include <ncurses.h>
#include <string>
#include <functional>
#include <memory>
#include "defns.h"
#include "Engine/Tag.h"

class GameObject;

typedef std::shared_ptr<GameObject> GameObjectSptr;


class GameObject
{
public:
    GameObject();
    GameObject(WINDOW* gameWin, int y=0, int x=0);

    virtual void Start(); // Called once when all objects are instantiated and loaded.
    virtual void Update(); // Our step function
    virtual void Draw(); // Draw our Game Object

    void setWin(WINDOW* newWin);
    WINDOW* getWin();  

    void setyx(int newY, int newX);
    void sety(int y);
    void setx(int x);

    virtual int gety();
    virtual int getx();

    virtual bool Collider(GameObjectSptr other);

    virtual ~GameObject() = default;

    void Destroy();
    bool isDestroyed();
    Tag getTag();
    void setTag(Tag newTag);

protected:
    std::string name;
    Tag tag;
    int y = 0;
    int x = 0;
    WINDOW* win = nullptr;
    bool destroy = false;
};



#endif //SNEK_GAMEOBJECT_H
