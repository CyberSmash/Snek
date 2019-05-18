//
// Created by jordan on 5/16/19.
//

#ifndef SNEK_ENGINEUTILS_H
#define SNEK_ENGINEUTILS_H
#include <memory>
#include <list>
#include "GameObject.h"

template <typename T> bool isType(std::shared_ptr<GameObject> object);

template<typename T>
bool isType(std::shared_ptr<GameObject> object);

std::list<std::shared_ptr<GameObject>> FindAllByTag(std::list<std::shared_ptr<GameObject>> gameObjects);

#endif //SNEK_ENGINEUTILS_H
