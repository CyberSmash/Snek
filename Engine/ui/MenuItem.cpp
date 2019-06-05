//
// Created by jordan on 6/4/19.
//

#include "MenuItem.h"

MenuItem::MenuItem(const wchar_t *label, std::function<void(void)> itemSelectedCallback) :
    itemLabel(label), callBack(std::move(itemSelectedCallback))
{

}
