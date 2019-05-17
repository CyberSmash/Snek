//
// Created by jordan on 5/16/19.
//

#include "EngineUtils.h"
#include <memory>

template <typename T>
bool isType(std::shared_ptr<GameObject> go)
{
    std::shared_ptr<T> tmp = std::dynamic_pointer_cast<T>(go);
    return tmp != nullptr;
}
