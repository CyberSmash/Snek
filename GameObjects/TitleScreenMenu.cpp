//
// Created by jordan on 5/26/19.
//

#include "TitleScreenMenu.h"
#include "Engine/Engine.h"
#include "Utils.h"

const wchar_t* MENU_NEW_GAME = L"NEW GAME";
const wchar_t* MENU_OPTIONS = L"OPTIONS";
const wchar_t* MENU_QUIT = L"QUIT";


TitleScreenMenu::TitleScreenMenu(WINDOW *gameWin, int y, int x) : GameObject(gameWin, y, x)
{

}

void TitleScreenMenu::Draw()
{

    box(win, 0, 0);
    int centerY = CenterY(win, menuItems.size());

    for (unsigned int i = 0; i < menuItems.size(); i++)
    {
        int centerX = CenterX(win, menuItems[i]);
        wmove(win, centerY + i, centerX);
        if (i == selectedItem)
        {
            wattron(win, COLOR_PAIR(1));
            wprintw(win, "%S", menuItems[i]);
            wattroff(win, COLOR_PAIR(1));

        }
        else
        {
            wattron(win, COLOR_PAIR(0));
            wprintw(win, "%S", menuItems[i]);
            wattroff(win, COLOR_PAIR(0));
        }
    }
}

void TitleScreenMenu::Update()
{
    int input = gameEngine->getInput();

    switch(input)
    {
        case KEY_UP:
            if (selectedItem == 0)
            {
                selectedItem = MenuItems::MAX_OPTIONS - 1;
                break;
            }
            selectedItem -= 1;
            break;
        case KEY_DOWN:
            if (selectedItem == MenuItems::MAX_OPTIONS - 1)
            {
                selectedItem = 0;
                break;
            }
            selectedItem += 1;
            break;
        case 10: // Enter key. KEY_ENTER is for the numpad.
            if (selectedItem == MenuItems::NEW_GAME)
            {
                gameEngine->changeScene("gameScene");
            }
            else if (selectedItem == MenuItems::QUIT)
            {
                gameEngine->quit();
            }

            break;

        default:
            break;
    }
}
