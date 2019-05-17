#include <iostream>
#include <ncurses.h>
#include <locale.h>
#include <chrono>
#include <thread>
#include "Snake.h"
#include "InputRouter.h"
#include "Food.h"
#include <random>
#include <time.h>
#include "Engine.h"
#include <memory>

#define Y 0
#define X 1

void setup_screen()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    nodelay(stdscr, true);
    curs_set(0);
}

int main() {
    std::srand(time(NULL));
    //const wchar_t* skulls = L"\u2620 Hello! \u2620";
    //const wchar_t* taco = {0xd83c, 0xdf2e};
    //const wchar_t* skulls = L"\u2502 Hello! \u2502";
    setlocale(LC_ALL, "");
    int WINMAX_Y = 20;
    int WINMAX_X = 40;
    // after this point stdscr is now available as well as
    //
    setup_screen();
    WINDOW* game_window = newwin(WINMAX_Y, WINMAX_X, 5, 5);
    nodelay(game_window, true);

    wclear(game_window);
    Engine e(game_window, 0);
    InputRouter inputRouter;
    auto player = std::make_shared<Snake>(game_window, 5, 5, 5, Direction::RIGHT);


    int foody = rand() % WINMAX_Y;
    int foodx = rand() % WINMAX_X;

    auto food = std::make_shared<Food>(game_window, foody, foodx);

    e.addGameObject(player);
    e.addGameObject(food);


    e.MainLoop();

    endwin();
    return 0;
}