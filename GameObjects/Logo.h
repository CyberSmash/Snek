//
// Created by jordan on 5/22/19.
//

#ifndef SNEK_LOGO_H
#define SNEK_LOGO_H
#include "GameObject.h"

extern const wchar_t* snek_logo[];
extern int snek_logo_size;
class Logo : public GameObject
{
public:
    Logo(WINDOW* gameWin, int y, int x);
    void Draw() override;
private:

};


#endif //SNEK_LOGO_H
