//
// Created by jordan on 5/20/19.
//

#include "AudioController.h"
#include "AudioEngine.h"
#include "Engine.h"

AudioController::AudioController() : GameObject(nullptr, 0, 0)
{

}

void AudioController::Update()
{
    if (gameEngine->getInput() == 'm')
    {
        audioEngine->ToggleMusic();
    }
}
