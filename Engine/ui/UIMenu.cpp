//
// Created by jordan on 6/4/19.
//

#include "GameObjects/Utils.h"
#include "UIMenu.h"
#include "Engine/Engine.h"

UIMenu::UIMenu(WINDOW *menuWindow, int y, int x) : GameObject(menuWindow, y, x)
{

}

void UIMenu::Update()
{
    int input = gameEngine->getInput();

    /**
     * This switch function doesn't provide the normal performance benefit from a switch statement using contiguous
     * numbering. It could as easily be an if statement, but for some reason I like the swtich statement here.
     */
    switch (input)
    {
        case KEY_UP:
            selectedItem--;
            if (selectedItem < 0)
            {
                selectedItem = menuItems.size() - 1;
            }
            break;

        case KEY_DOWN:
            selectedItem = (selectedItem + 1) % menuItems.size();
            break;

        case KEY_ENTER:
        case 10:
            if (menuItems[selectedItem].callBack != nullptr)
            {
                menuItems[selectedItem].callBack();
            }
            break;
        default:
            break;
    }

}

/**
 * Draw our menu.
 *
 * @TODO: I still have references in here for alignment, but really that should be handled elsewhere. Possibly
 * I should extend the MenuItem class to include X/Y coords.
 */
void UIMenu::Draw()
{

    //box(win, 0, 0);
    int centerY = CenterY(win, menuItems.size());

    for (unsigned int i = 0; i < menuItems.size(); i++)
    {
        int centerX = CenterX(win, menuItems[i].itemLabel);
        wmove(win, centerY + i, centerX);
        if (i == selectedItem)
        {
            wattron(win, COLOR_PAIR(1));
            wprintw(win, "%S", menuItems[i].itemLabel);
            wattroff(win, COLOR_PAIR(1));
        }
        else
        {
            wattron(win, COLOR_PAIR(0));
            wprintw(win, "%S", menuItems[i].itemLabel);
            wattroff(win, COLOR_PAIR(0));
        }
    }
}
