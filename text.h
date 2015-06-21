#pragma once

#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <sstream>

#include "gameinterface.h"
#include "graphics.h"

class Text
{
private:
    GameInterface* game;
    const char* message;
    Rect rect;
    SDL_Color color;
    TTF_Font* font;
    SDL_Texture* texture;
public:
    void init(GameInterface *game, char* message, SDL_Color color, char *file, Rect rect);
    void init(GameInterface *game, int message, SDL_Color color, char *file, Rect rect);
    void changeMessage(const char* message);
    void changeMessage(int number);
    void draw() const;
    void quit();
};
