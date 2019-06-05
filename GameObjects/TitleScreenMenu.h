//
// Created by jordan on 5/26/19.
//

#ifndef SNEK_TITLESCREENMENU_H
#define SNEK_TITLESCREENMENU_H

#include <vector>
#include "Engine/ui/UIMenu.h"
#include "Engine/ui/MenuItem.h"
#include "GameObject.h"

extern const wchar_t* MENU_NEW_GAME;
extern const wchar_t* MENU_OPTIONS;
extern const wchar_t* MENU_QUIT;

enum MenuItems
{
    NEW_GAME,
    OPTIONS,
    QUIT,
    MAX_OPTIONS,
};

class TitleScreenMenu : public UIMenu
{

public:
    TitleScreenMenu(WINDOW* gameWin, int y, int x);
    void Draw() override;
    void Update() override;
    static void startGame();
    static void quitGame();
    static void optionsScreen();
protected:

};


#endif //SNEK_TITLESCREENMENU_H
