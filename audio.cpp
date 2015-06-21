#include "audio.h"


void Audio::init(char *file)
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    this->audio = Mix_LoadMUS(file);
}

void Audio::play() const
{
    Mix_PlayMusic (this->audio, -1);
}

void Audio::stop()
{
    Mix_HaltMusic();
}

void Audio::quit()
{
    Mix_FreeMusic(this->audio);
    Mix_CloseAudio();
}
