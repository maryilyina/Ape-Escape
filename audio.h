#pragma once

#include <SDL2/SDL_mixer.h>

class Audio
{
private:
    Mix_Music* audio;
public:
    void init(char* file);
    void play() const;
    void stop();
    void quit();
};
