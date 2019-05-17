//
// Created by jordan on 5/16/19.
//

#ifndef SNEK_ENGINEUTILS_H
#define SNEK_ENGINEUTILS_H
#include <memory>
#include "GameObject.h"

template <typename T> bool isType(std::shared_ptr<GameObject> object);

template<typename T>
bool isType(std::shared_ptr<GameObject> object);
#endif //SNEK_ENGINEUTILS_H
