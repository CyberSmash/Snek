//
// Created by jordan on 5/22/19.
//

#include <ncurses.h>

#include "TitleScreen.h"
#include "GameObjects/Logo.h"
#include "GameObjects/Utils.h"
#include "GameObjects/TitleScreenMenu.h"

#define MAX_TOTAL_X 80
#define MAX_TOTAL_Y 40

TitleScreen::TitleScreen(std::string sceneName) : Scene(std::move(sceneName))
{

    int     logo_win_height     = MAX_TOTAL_Y * 0.66;
    int     windows_start_draw  = (getmaxx(stdscr) / 2) - (MAX_TOTAL_X / 2);
    int     menu_win_height     = MAX_TOTAL_Y * 0.33;
    int     windows_y_start_draw = (getmaxy(stdscr) / 2) - (logo_win_height + menu_win_height)  / 2;

    WINDOW* logo_window     = newwin(logo_win_height, MAX_TOTAL_X, windows_y_start_draw, windows_start_draw);
    WINDOW* menu_window     = newwin(menu_win_height, MAX_TOTAL_X, windows_y_start_draw + getmaxy(logo_window) + 1, windows_start_draw);

    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_BLACK, COLOR_WHITE);

    //nodelay(logo_window, true);
    windows.emplace_back(logo_window);
    windows.emplace_back(menu_window);
}

void TitleScreen::LoadScene()
{
    // Resize the window passed to us.
    WINDOW* win = windows[WINDOW_TAG::LOGO_AREA];
    int centerX = CenterX(win, snek_logo[0]);
    int centerY = CenterY(win, snek_logo_size);
    gameObjects.emplace_back(std::make_shared<Logo>(win, centerY, centerX));
    gameObjects.emplace_back(std::make_shared<TitleScreenMenu>(windows[1], 0, 0));
}

void TitleScreen::UnloadScene()
{
    for (auto win : windows)
    {
        delwin(win);
    }
}

