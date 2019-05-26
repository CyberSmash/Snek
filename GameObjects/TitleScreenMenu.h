//
// Created by jordan on 5/26/19.
//

#ifndef SNEK_TITLESCREENMENU_H
#define SNEK_TITLESCREENMENU_H

#include <vector>
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

class TitleScreenMenu : public GameObject
{

public:

    TitleScreenMenu(WINDOW* gameWin, int y, int x);
    void Draw() override;
    void Update() override;

protected:
    unsigned int selectedItem {0};
    std::vector<const wchar_t*> menuItems  {MENU_NEW_GAME,
                                            MENU_OPTIONS,
                                            MENU_QUIT};
};


#endif //SNEK_TITLESCREENMENU_H
