//
// Created by jordan on 6/4/19.
//

#ifndef SNEK_MENUITEM_H
#define SNEK_MENUITEM_H

#include <functional>

class MenuItem
{
public:
    MenuItem(const wchar_t* label, std::function<void(void)> itemSelectedCallback);

    const wchar_t*              itemLabel   {nullptr};
    std::function<void(void)>   callBack    {nullptr};
};


#endif //SNEK_MENUITEM_H
