//
// Created by jordan on 5/26/19.
//

#include "TitleScreenMenu.h"
#include "Engine/Engine.h"
#include "Utils.h"

const wchar_t* MENU_NEW_GAME = L"NEW GAME";
const wchar_t* MENU_OPTIONS = L"OPTIONS";
const wchar_t* MENU_QUIT = L"QUIT";


TitleScreenMenu::TitleScreenMenu(WINDOW *gameWin, int y, int x) : UIMenu(gameWin, y, x)
{
    menuItems.emplace_back(MENU_NEW_GAME, startGame);
    menuItems.emplace_back(MENU_OPTIONS, optionsScreen);
    menuItems.emplace_back(MENU_QUIT, quitGame);
}

void TitleScreenMenu::Draw()
{
    box(win, 0, 0);
    UIMenu::Draw();
}

void TitleScreenMenu::Update()
{
    UIMenu::Update();
}

void TitleScreenMenu::startGame()
{
    gameEngine->changeScene("gameScene");
}

void TitleScreenMenu::quitGame()
{
    gameEngine->quit();
}

void TitleScreenMenu::optionsScreen()
{
    gameEngine->changeScene("optionsScene");
}