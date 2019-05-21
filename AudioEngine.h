//
// Created by jordan on 5/20/19.
//

#ifndef SNEK_AUDIOENGINE_H
#define SNEK_AUDIOENGINE_H

#include <SDL.h>
#include <SDL_mixer.h>

#include <memory>
#include <vector>


/**
 * I actually do not want AudioTags to be strongly typed since I will use them to
 * access the sound effects vector by index.
 */
typedef enum _AudioTag
{
    EAT_FOOD,
    EXPLODE,
    GAME_OVER,
    AUDIO_TAG_END,
} AudioTag;


class AudioEngine
{
public:
    AudioEngine();
    void PlaySound(AudioTag tag);
    void StopMusic();
    void ToggleMusic();
    void PlayMusic();
    ~AudioEngine();
private:

    std::vector<Mix_Chunk*> mixes;
    Mix_Music* music;
};

extern std::shared_ptr<AudioEngine> audioEngine;


#endif //SNEK_AUDIOENGINE_H
