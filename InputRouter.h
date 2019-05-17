//
// Created by jordan on 5/8/19.
//

#ifndef SNEK_INPUTROUTER_H
#define SNEK_INPUTROUTER_H

#include <ncurses.h>
#include <queue>
#include <vector>


using std::queue;
using std::vector;

struct WindowInput
{
    WINDOW* win;
    queue<int> input;
};

class InputRouter
{
public:
    InputRouter();
    void checkInput();
    int getInput();
    void setWindow(WINDOW* win);
private:
    static int input;
    static WINDOW* win;
};


#endif //SNEK_INPUTROUTER_H
