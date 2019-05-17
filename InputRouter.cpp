//
// Created by jordan on 5/8/19.
//

#include "InputRouter.h"

int InputRouter::input = ERR;
WINDOW* InputRouter::win = nullptr;

InputRouter::InputRouter()
{
    InputRouter::input = ERR;
}

void InputRouter::checkInput()
{
    InputRouter::input = wgetch(InputRouter::win);
}

int InputRouter::getInput()
{
    return InputRouter::input;
}

void InputRouter::setWindow(WINDOW *input_window)
{
    InputRouter::win = input_window;
}
