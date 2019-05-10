//
// Created by jordan on 5/8/19.
//

#ifndef SNEK_GAMEOBJECT_H
#define SNEK_GAMEOBJECT_H

#include "defns.h"
#include <ncurses.h>
#include <tuple>

using std::tuple;

class GameObject
{
public:

    GameObject(WINDOW* win, int y=0, int x=0);
    virtual void Update() = 0; // Our step function
    virtual void Draw() = 0; // Draw our Game Object

    void setWin(WINDOW* newWin);
    WINDOW* getWin();

    void setyx(int newY, int newX);
    void sety(int y);
    void setx(int x);

    int gety();
    int getx();

    ~GameObject() = default;

protected:
    int y;
    int x;
    WINDOW* win;
};


#endif //SNEK_GAMEOBJECT_H
