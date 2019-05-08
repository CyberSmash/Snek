#include <iostream>
#include <ncurses.h>
#include <locale.h>


#define Y 0
#define X 1

void setup_screen()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    timeout(-1);
}

int main() {

    //const wchar_t* skulls = L"\u2620 Hello! \u2620";
    //const wchar_t* taco = {0xd83c, 0xdf2e};
    const wchar_t* skulls = L"\u2502 Hello! \u2502";
    setlocale(LC_ALL, "");

    // after this point stdscr is now available as well as
    //
    setup_screen();

    clear();
    //attron(A_BOLD);
    mvaddwstr(5, 5, skulls);
    //attroff(A_BOLD);
    getch();
    endwin();
    return 0;
}