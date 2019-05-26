//
// Created by jordan on 5/26/19.
//

#include "Utils.h"

int CenterX(WINDOW *win, const wchar_t* string)
{
    int maxx            = getmaxx(win);
    int string_length   = wcslen(string);
    int center = (maxx / 2) - (string_length / 2);
    return center;

}

int CenterY(WINDOW *win, int num_lines)
{
    int maxy = getmaxy(win);
    return (maxy / 2) - (num_lines / 2);
}
