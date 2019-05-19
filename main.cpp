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
#include "GameRunner.h"
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

int main()
{

    setlocale(LC_ALL, "");
    int WINMAX_Y = 20;
    int WINMAX_X = 40;
    // after this point stdscr is now available as well as
    setup_screen();
    WINDOW* game_window = newwin(WINMAX_Y, WINMAX_X, 5, 5);
    nodelay(game_window, true);

    wclear(game_window);

    gameEngine = std::make_shared<Engine>(game_window, 1);

    std::shared_ptr<GameRunner> runner = std::make_shared<GameRunner>(game_window);

    gameEngine->addGameObject(runner);
    gameEngine->MainLoop();

    endwin();
    return 0;
}