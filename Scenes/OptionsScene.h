//
// Created by jordan on 6/3/19.
//

#ifndef SNEK_OPTIONSSCENE_H
#define SNEK_OPTIONSSCENE_H

#include "Engine/Scene.h"

class OptionsScene : public Scene
{
public:
    enum WINDOW_TAG
    {
        OPTIONS_MENU,
    };

    explicit OptionsScene(std::string sceneName);
    void LoadScene() override;
    void UnloadScene() override;
};


#endif //SNEK_OPTIONSSCENE_H
