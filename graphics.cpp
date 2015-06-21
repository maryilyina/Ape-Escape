#include "graphics.h"

Rect::Rect(float x, float y, float w, float h)
{
    this->set_x(x);
    this->set_y(y);
    this->set_w(w);
    this->set_h(h);
}

void Rect::init(float x, float y, float w, float h)
{
    this->set_x(x);
    this->set_y(y);
    this->set_w(w);
    this->set_h(h);
}

void Rect::init(Rect rect)
{
    this->set_x(rect.get_x());
    this->set_y(rect.get_y());
    this->set_w(rect.get_w());
    this->set_h(rect.get_h());
}

void Object::init(GameInterface* game, char* file, Rect rect)
{
    this->game = game;
    this->texture = NULL;

    SDL_Surface* surface;
    surface = IMG_Load(file);
    this->texture = SDL_CreateTextureFromSurface(this->game->getRenderer(), surface);
    SDL_FreeSurface(surface);

    this->rect.init(rect);
}

void Object::draw() const
{
    SDL_Rect t_rect;

    t_rect.x = (int) (this->rect.get_x());
    t_rect.y = (int) (this->rect.get_y());
    t_rect.w = (int) (this->rect.get_w());
    t_rect.h = (int) (this->rect.get_h());

    SDL_RenderCopy(this->game->getRenderer(), this->texture, NULL, &(t_rect));
}

void Object::quit()
{
    SDL_DestroyTexture(this->texture);
}


void Button::init(GameInterface* game, char* file, Rect rect, void (*action) (GameInterface*))
{
    this->game = game;
    this->but_body.init(game, file, rect);
    this->action = action;
}

void Button::quit()
{
    this->but_body.quit();
}

void PhObject::init(GameInterface* game, char* file, Rect rect)
{
    this->init(game, file, rect, 0, 0, 0);
}


void PhObject::init(GameInterface* game, char* file, Rect rect, float vx, float vy, float vw)
{
    this->game = game;
    this->texture = NULL;

    SDL_Surface* surface;
    surface = IMG_Load(file);
    this->texture = SDL_CreateTextureFromSurface(this->game->getRenderer(), surface);
    SDL_FreeSurface(surface);

    this->initial_rect.init(rect);
    this->initial_vx = vx;
    this->initial_vy = vy;
    this->rect.init(rect);

    this->set_vx(vx);
    this->set_vy(vy);
    this->set_vw(vw);
    this->setAngle(0);
    this->setLast_x(this->get_x());
    this->setLast_y(this->get_y());
}

void PhObject::reset()
{
    this->rect.init(this->initial_rect);
    this->set_vx(this->initial_vx);
    this->set_vy(this->initial_vy);
    this->set_vw(0);
    this->setAngle(0);
    this->setLast_x(this->get_x());
    this->setLast_y(this->get_y());
}

void PhObject::draw() const
{
    SDL_Rect t_rect;

    t_rect.x = (int) (this->rect.get_x());
    t_rect.y = (int) (this->rect.get_y());
    t_rect.w = (int) (this->rect.get_w());
    t_rect.h = (int) (this->rect.get_h());

    SDL_RenderCopyEx(this->game->getRenderer(), this->texture, NULL, &(t_rect), this->getAngle(), NULL, SDL_FLIP_NONE);
}
