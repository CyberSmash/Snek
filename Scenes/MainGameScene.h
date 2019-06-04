//
// Created by jordan on 5/21/19.
//

#ifndef SNEK_MAINGAMESCENE_H
#define SNEK_MAINGAMESCENE_H

#include <string>
#include "Engine/Scene.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Snake.h"
#include "GameObjects/Food.h"
#include "GameObjects/AudioController.h"
#include "GameObjects/GameRunner.h"
#include "GameObjects/AISnake.h"
#include "GameObjects/ScoreBoard.h"
class MainGameScene : public Scene
{

public:
    enum WINDOW_TAG
    {
        GAME_AREA,
        SCORE_BOARD,
    };
    MainGameScene(std::string sceneName);
    void LoadScene() override;
    void UnloadScene() override;
private:

};


#endif //SNEK_MAINGAMESCENE_H
