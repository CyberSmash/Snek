//
// Created by jordan on 6/4/19.
//
#include "Engine/Engine.h"
#include "OptionsMenu.h"

const wchar_t* OPTION_MUSIC_STRING = L"MUSIC";
const wchar_t* OPTION_SOUNDFX_STRING = L"SOUNDFX";
const wchar_t* OPTION_AI_STRING = L"SNAKE AI";
const wchar_t* OPTION_BACK = L"MAIN MENU";

OptionsMenu::OptionsMenu(WINDOW *menuWindow, ALIGNMENT item_alignment, int y, int x) : UIMenu(menuWindow, item_alignment, y, x)
{
    menuItems.emplace_back(OPTION_MUSIC_STRING,   nullptr);
    menuItems.emplace_back(OPTION_SOUNDFX_STRING, nullptr);
    menuItems.emplace_back(OPTION_AI_STRING,      nullptr);
    menuItems.emplace_back(OPTION_BACK,           goBack);
}

void OptionsMenu::Update()
{
    UIMenu::Update();
}

void OptionsMenu::Draw()
{
    box(win, 0, 0);
    UIMenu::Draw();
}

void OptionsMenu::goBack()
{
    gameEngine->changeScene("titleScreen");
}
