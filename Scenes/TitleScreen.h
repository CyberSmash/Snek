//
// Created by jordan on 5/22/19.
//

#ifndef SNEK_TITLESCREEN_H
#define SNEK_TITLESCREEN_H
#include "Engine/Scene.h"

class TitleScreen : public Scene
{

public:
    enum WINDOW_TAG
    {
        LOGO_AREA,
        MENU_AREA,
    };
    TitleScreen(std::string sceneName);
    void LoadScene() override;
    void UnloadScene() override;
};

#endif //SNEK_TITLESCREEN_H
