//
// Created by jordan on 5/22/19.
//

#include "Logo.h"
#include <ncurses.h>

const wchar_t* snek_logo[] = {L"███████╗███╗   ██╗███████╗██╗  ██╗",
                              L"██╔════╝████╗  ██║██╔════╝██║ ██╔╝",
                              L"███████╗██╔██╗ ██║█████╗  █████╔╝ ",
                              L"╚════██║██║╚██╗██║██╔══╝  ██╔═██╗ ",
                              L"███████║██║ ╚████║███████╗██║  ██╗",
                              L"╚══════╝╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝",
                              L"                                  "};
int snek_logo_size = 7;

Logo::Logo(WINDOW *logoWin, int y, int x) : GameObject(logoWin, y, x)
{


}

void Logo::Draw()
{
    wclear(win);
    box(win, 0, 0);

    for (int i = 0; i < snek_logo_size; i++)
    {

        wmove(win, gety() + i, getx());
        wprintw(win, "%S", snek_logo[i]);

    }
    wrefresh(win);

}
