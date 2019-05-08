//
// Created by jordan on 5/8/19.
//

#include "InputRouter.h"

InputRouter::InputRouter()
{
    this->input = ERR;
}

void InputRouter::checkInput()
{
    this->input = getch();
}

int InputRouter::getInput()
{
    return this->input;
}
