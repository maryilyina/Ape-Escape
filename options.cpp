#include "gamestates.h"

#define BTN_OK                0
#define BTN_ON                1
#define BTN_OFF               2
#define BTN_BANANA_TYPE_1     3
#define BTN_BANANA_TYPE_2     4
#define BTN_BANANA_TYPE_3     5
#define BTN_BANANA_TYPE_4     6


void Options::init(GameInterface* game)
{
    this->game = game;

    Rect t_rect(0, 0, SCREEN_W, SCREEN_H);
    this->background.init(game, "./sources/options_background.png", t_rect);

    t_rect.init(1166, 0, 200, 100);
    this->btns[BTN_OK].init(game, "./sources/options_btn_ok.png", t_rect, &this->goBackFromOptions);

    t_rect.init(100, 300, 300, 100);
    this->music.init(game, "./sources/options_music.png", t_rect);

    t_rect.init(600, 300, 300, 100);
    this->btns[BTN_ON].init(game, "./sources/options_btn_on.png", t_rect, &this->actMusicOn);

    t_rect.init(1000, 300, 300, 100);
    this->btns[BTN_OFF].init(game, "./sources/options_btn_off.png", t_rect, &this->actMusicOff);

    t_rect.init(200, 550, 200, 150);
    this->btns[BTN_BANANA_TYPE_1].init(game, "./sources/options_btn_banana1.png", t_rect, &this->actSetBananaType1);

    t_rect.init(450, 550, 200, 150);
    this->btns[BTN_BANANA_TYPE_2].init(game, "./sources/options_btn_banana2.png", t_rect, &this->actSetBananaType2);

    t_rect.init(700, 550, 200, 150);
    this->btns[BTN_BANANA_TYPE_3].init(game, "./sources/options_btn_banana3.png", t_rect, &this->actSetBananaType3);

    t_rect.init(950, 550, 200, 150);
    this->btns[BTN_BANANA_TYPE_4].init(game, "./sources/options_btn_banana4.png", t_rect, &this->actSetBananaType4);
}

void Options::drawGraphics() const
{
    this->background.draw();
    this->music.draw();

    for (int i = 0; i < OPTIONS_BTNS_COUNT; i++)
        this->btns[i].draw();
}

void Options::process()
{
    this->game->setCurTime(SDL_GetTicks());
    this->drawGraphics();
    this->processInput();
}

void Options::processInput()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
       if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
                this->goBackFromOptions(this->game);
        }

       if (event.type==SDL_MOUSEBUTTONDOWN)
       {
           int mx = event.motion.x;
           int my = event.motion.y;
           for (int i = 0; i < OPTIONS_BTNS_COUNT; i++)
           {
               Button t_btn = btns[i];
               Rect t_rect = btns[i].getRect();
               if (mx > t_rect.get_x() && mx < t_rect.get_x() + t_rect.get_w() &&
                   my > t_rect.get_y() && my < t_rect.get_y() + t_rect.get_h())
                   t_btn.perform_action();
           }
       }
    }
}

void Options::quit()
{
    this->background.quit();
    this->music.quit();
    for (int i = 0; i < OPTIONS_BTNS_COUNT; i++)
        this->btns[i].quit();
}

