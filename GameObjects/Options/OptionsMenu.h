//
// Created by jordan on 6/4/19.
//

#ifndef SNEK_OPTIONSMENU_H
#define SNEK_OPTIONSMENU_H

#include <vector>
#include "Engine/ui/MenuItem.h"
#include "Engine/ui/UIMenu.h"



class OptionsMenu : public UIMenu
{
public:
    OptionsMenu(WINDOW* menuWindow, int y, int x);
    void Update() override;
    void Draw() override;
private:
    static void goBack();

};


#endif //SNEK_OPTIONSMENU_H
