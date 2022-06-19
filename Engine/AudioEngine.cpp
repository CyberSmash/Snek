//
// Created by jordan on 5/20/19.
//

#include "AudioEngine.h"
#include <exception>
#include <stdexcept>

#define EAT_FOOD_FILE "../audio/leisure_video_game_retro_8bit_object_pickup_collect.wav"
#define BACKGROUND_MUSIC_FILE "../audio/PM_ATG_3_110BPM_E.wav"



AudioEngine::AudioEngine()
{
    /**
     * Yes, I think resize is the correct choice over reserve. I need a vector
     * to have all of the possible slots available all the time.
     */
    mixes.resize(AudioTag::AUDIO_TAG_END, nullptr);
    int result = SDL_Init(SDL_INIT_AUDIO);
    if (result < 0)
    {
        throw std::runtime_error("Cannot initialize SDL audio.");
    }

    result = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    if (result < 0)
    {
        throw std::runtime_error("Mixer could not be opened!");
    }

    mixes[AudioTag::EAT_FOOD] = Mix_LoadWAV(EAT_FOOD_FILE);
    if (mixes[AudioTag::EAT_FOOD] == nullptr)
    {
        throw std::runtime_error("Cannot find EAT_FOOD_FILE.");
    }

    music = Mix_LoadMUS(BACKGROUND_MUSIC_FILE);
    if (music == nullptr)
    {
        throw std::runtime_error("Cannot find music file.");
    }
}


/**
 * Play the tagged file.
 *
 * @note: this is for one-shot sound clips like FX.
 *
 * @param tag The tag to play.
 */
void AudioEngine::PlaySound(AudioTag tag)
{
    Mix_PlayChannel(-1, mixes[tag], 0);
}


/**
 * Play the music. Will resume if pause (unimplemented) was chosen.
 */
void AudioEngine::PlayMusic()
{
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(music, -1);
    }
}


/**
 * Stop the music. Will restart at the beginning.
 */
void AudioEngine::StopMusic()
{
    if (Mix_PlayingMusic())
    {
        Mix_HaltMusic();
    }
}


void AudioEngine::ToggleMusic()
{
    if(Mix_PlayingMusic())
    {
        Mix_HaltMusic();
        return;
    }
    Mix_PlayMusic(music, -1);
}


AudioEngine::~AudioEngine()
{
    for (Mix_Chunk* chunk : mixes)
    {
        Mix_FreeChunk(chunk);
    }

    Mix_FreeMusic(music);

    Mix_Quit();
    SDL_Quit();
}

std::shared_ptr<AudioEngine> audioEngine = std::make_shared<AudioEngine>();
