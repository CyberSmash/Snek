#include <iostream>
#include <ncurses.h>
#include <locale.h>
#include <chrono>
#include <thread>
#include "GameObjects/Snake.h"
#include "Engine/InputRouter.h"
#include "GameObjects/Food.h"
#include <random>
#include <time.h>
#include "Engine/Engine.h"
#include "GameObjects/GameRunner.h"
#include "Engine/AudioEngine.h"
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
    start_color();
}

int main()
{

    setlocale(LC_ALL, "");
    // after this point stdscr is now available as well as
    setup_screen();
    gameEngine = std::make_shared<Engine>(0);


    gameEngine->MainLoop();

    endwin();
    return 0;
}