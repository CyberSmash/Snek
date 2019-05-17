//
// Created by jordan on 5/8/19.
//

#ifndef SNEK_GAMEOBJECT_H
#define SNEK_GAMEOBJECT_H

#include <ncurses.h>
#include <tuple>
#include <string>
#include <functional>
#include <memory>
#include "defns.h"
#include "Tag.h"
using std::tuple;

class GameObject
{
public:
    GameObject();
    GameObject(WINDOW* gameWin, int y=0, int x=0);
    virtual void Update(); // Our step function
    virtual void Draw(); // Draw our Game Object

    void setWin(WINDOW* newWin);
    WINDOW* getWin();  

    void setyx(int newY, int newX);
    void sety(int y);
    void setx(int x);

    virtual int gety();
    virtual int getx();

    virtual bool Collider(std::shared_ptr<GameObject> other);

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
