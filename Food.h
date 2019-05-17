//
// Created by jordan on 5/10/19.
//

#ifndef SNEK_FOOD_H
#define SNEK_FOOD_H

#include "GameObject.h"
#include <memory>

class Food : public GameObject
{
public:
    Food(WINDOW* foodwin, int y, int x);
    ~Food() = default;
    void Update() override;
    void Draw() override;
    bool Collider(std::shared_ptr<GameObject> other) override;
protected:
    int segment_value = 1;
private:



};

#endif //SNEK_FOOD_H
