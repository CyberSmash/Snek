//
// Created by jordan on 5/20/19.
//

#include "AudioController.h"
#include "Engine/AudioEngine.h"
#include "Engine/Engine.h"

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
