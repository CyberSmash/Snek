//
// Created by jordan on 6/4/19.
//

#include "GameObjects/Utils.h"
#include "UIMenu.h"
#include "Engine/Engine.h"

/**
 * Constructor.
 * @param menuWindow The window to draw the menu.
 * @param y The y coordinate of the menu.
 * @param x The x coordinate of the menu.
 */
UIMenu::UIMenu(WINDOW *menuWindow, int y, int x) : GameObject(menuWindow, y, x)
{

}

/**
 * UIMenu update function
 *
 * Read in input from the game Engine, then if the up arrow or down arrow are used, select the next menu item.
 * If the enter button is hit, then select that menu item.
 */
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
            if (selectedItem == 0)
            {
                selectedItem = menuItems.size() - 1;
            }
            else
            {
                selectedItem = (selectedItem - 1) % menuItems.size();
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
