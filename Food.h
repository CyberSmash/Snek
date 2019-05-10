//
// Created by jordan on 5/10/19.
//

#ifndef SNEK_FOOD_H
#define SNEK_FOOD_H

#include "GameObject.h"

class Food : public GameObject
{
public:
    Food();
    Food(WINDOW* win, int y, int x);

    void Update();
    void Draw();

protected:
    int segment_value = 1;
    WINDOW* win = nullptr;

};


#endif //SNEK_FOOD_H
