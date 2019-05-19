//
// Created by jordan on 5/8/19.
//

#ifndef SNEK_DEFNS_H
#define SNEK_DEFNS_H

#include <memory>
#include "GameObject.h"

// Easily remember if Y comes first or X comes first, also helps
// when indexing into a tuple.
#define Y 0
#define X 1

enum class Direction
{
    UP      = 0,
    RIGHT   = 1,
    DOWN    = 2,
    LEFT    = 3,
};

#endif //SNEK_DEFNS_H
