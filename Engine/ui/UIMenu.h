/**
 * An abstracted way to create UI Menu's.
 *
 * @TODO: It may make more sense if UI Items extend from a UI class, but the way the engine works,
 * there doesn't appear to be any good reason why they would need to.
 */

#ifndef SNEK_UIMENU_H
#define SNEK_UIMENU_H

#include "GameObjects/GameObject.h"
#include <vector>
#include "Engine/ui/MenuItem.h"

class UIMenu : public GameObject
{
public:

    UIMenu(WINDOW* menuWindow, int y, int x);
    void Update() override;
    void Draw() override;

protected:
    unsigned int selectedItem    {0};
    std::vector<MenuItem> menuItems {};
};


#endif //SNEK_UIMENU_H
