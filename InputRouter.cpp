//
// Created by jordan on 5/8/19.
//

#include "InputRouter.h"

int InputRouter::input = ERR;

InputRouter::InputRouter()
{
    InputRouter::input = ERR;
}

void InputRouter::checkInput()
{
    InputRouter::input = getch();
}

int InputRouter::getInput()
{
    return InputRouter::input;
}