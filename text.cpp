#include "text.h"

void Text::init(GameInterface *game, char* message, SDL_Color color, char *file, Rect rect)
{
    this->game = game;
    this->texture = NULL;
    this->color = color;
    this->font = TTF_OpenFont(file, 70);
    this->message = message;

    SDL_Surface* surface;
    surface = TTF_RenderText_Blended(font, message, color);
    this->texture = SDL_CreateTextureFromSurface(game->getRenderer(), surface);

    SDL_FreeSurface(surface);

    this->rect = rect;
}

void Text::init(GameInterface *game, int message, SDL_Color color, char *file, Rect rect)
{
    this->game = game;
    this->texture = NULL;
    this->color = color;
    this->font = TTF_OpenFont(file, 70);

    std::stringstream ss;
    ss << message;
    std::string result = ss.str();
    const char * c = result.c_str();
    this->changeMessage(c);

    SDL_Surface* surface;
    surface = TTF_RenderText_Blended(font, this->message, color);
    this->texture = SDL_CreateTextureFromSurface(game->getRenderer(), surface);

    SDL_FreeSurface(surface);

    this->rect = rect;
}

void Text::changeMessage(const char* message)
{
    this->message = message;

    SDL_Surface* surface;
    surface = TTF_RenderText_Blended(font, message, color);
    this->texture = SDL_CreateTextureFromSurface(game->getRenderer(), surface);

    SDL_FreeSurface(surface);
}

void Text::changeMessage(int number)
{
    std::stringstream ss;
    ss << number;
    std::string result = ss.str();
    const char * c = result.c_str();
    this->changeMessage(c);
}

void Text::draw() const
{
    SDL_Rect t_rect;
    t_rect.x = rect.get_x();
    t_rect.y = rect.get_y();
    t_rect.w = rect.get_w();
    t_rect.h = rect.get_h();
    SDL_RenderCopy(this->game->getRenderer(), this->texture, NULL, &(t_rect));
}

void Text::quit()
{
    TTF_CloseFont(font);
}
