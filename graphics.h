#pragma once

#include <SDL2/SDL_image.h>
#include "gameinterface.h"

class Rect
{
private:
    float x;
    float y;
    float w;
    float h;
public:
    Rect() {}
    Rect(float x, float y, float w, float h);
    void init(float x, float y, float w, float h);
    void init(Rect rect);
    float get_x() const {return this->x;}
    float get_y() const {return this->y;}
    float get_w() const {return this->w;}
    float get_h() const {return this->h;}

    void set_x(float s) {this->x = s;}
    void set_y(float s) {this->y = s;}
    void set_w(float s) {this->w = s;}
    void set_h(float s) {this->h = s;}
};

class Object
{
protected:
    GameInterface* game;
    SDL_Texture* texture;
    Rect rect;
public:
    void init(GameInterface* game, char* file, Rect rect);
    void draw() const;
    void quit();
    Rect getRect() {return this->rect;}

    float get_x() const   {return this->rect.get_x();}
    float get_y() const   {return this->rect.get_y();}
    float get_w() const   {return this->rect.get_w();}
    float get_h() const   {return this->rect.get_h();}
    void  set_x(float x)  {this->rect.set_x(x);}
    void  set_y(float y)  {this->rect.set_y(y);}
};

class PhObject : public Object
{
private:
    Rect initial_rect;
    int angle;
    float vx;
    float vy;
    float initial_vx;
    float initial_vy;
    float vw;
    float last_x;
    float last_y;
public:
    void init(GameInterface* game, char* file, Rect rect);
    void init(GameInterface* game, char* file, Rect rect, float vx, float vy, float vw);
    void draw() const;
    void reset();

    float get_vx()   const {return this->vx;}
    float get_vy()   const {return this->vy;}
    float get_vw()   const {return this->vw;}
    int   getAngle() const {return this->angle;}

    void  set_vx(float v)  {this->vx = v;}
    void  set_vy(float v)  {this->vy = v;}
    void  set_vw(float v)  {this->vw = v;}
    void  setAngle(int a)  {this->angle = a;}

    float getLast_x() const {return this->last_x;}
    float getLast_y() const {return this->last_y;}
    void  setLast_x(float x){this->last_x = x;}
    void  setLast_y(float y){this->last_y = y;}
};

class Button
{
private:
    GameInterface* game;
    Object but_body;
    void (*action) (GameInterface* game);
public:
    void init(GameInterface* game, char* file, Rect rect, void (*action)(GameInterface*));
    void draw() const {this->but_body.draw();}
    void perform_action() {action(this->game);}
    Rect getRect() {return this->but_body.getRect();}
    void quit();
};

