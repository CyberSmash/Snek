//
// Created by jordan on 5/20/19.
//

#ifndef SNEK_AUDIOCONTROLLER_H
#define SNEK_AUDIOCONTROLLER_H
#include "GameObject.h"

class AudioController: public GameObject
{
public:
    AudioController();
    ~AudioController() = default;

    void Update() override;
};


#endif //SNEK_AUDIOCONTROLLER_H
